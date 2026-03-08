// Mendb11.cpp
// Win32 + WGL(OpenGL) display + OpenCL compute (CL/GL sharing)
// + Stable Archetype Library: 100-Equation Modular Mathematical Framework
// + 5 fixed neural archetypes with context-conditioned blending
// + LibTorch for weight initialization, OpenCL for per-pixel inference
//
// Pipeline: c_t -> π(t) -> o_{k,p,t} -> o_{p,t} -> I_{p,t}
//
// GPU Performance Architecture:
// - CPU (LibTorch): Context evolution + Controller (1x per frame)
// - GPU (OpenCL): All 100 equations evaluated in parallel for all pixels
// - GPU (OpenGL): Zero-copy display via CL/GL shared PBO

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#ifndef NOMINMAX
#define NOMINMAX
#endif

#define _CRT_SECURE_NO_WARNINGS

// ============================================================
// 1) Include LibTorch FIRST
// ============================================================
#if defined(__has_include)
  #if __has_include(<torch/torch.h>) && __has_include(<torch/script.h>)
    #include <torch/torch.h>
    #include <torch/script.h>
  #elif __has_include("D:/libtorch-win-shared-with-deps-2.4.0+cu124/libtorch/include/torch/csrc/api/include/torch/torch.h") && \
        __has_include("D:/libtorch-win-shared-with-deps-2.4.0+cu124/libtorch/include/torch/script.h")
    #include "D:/libtorch-win-shared-with-deps-2.4.0+cu124/libtorch/include/torch/csrc/api/include/torch/torch.h"
    #include "D:/libtorch-win-shared-with-deps-2.4.0+cu124/libtorch/include/torch/script.h"
  #else
    #error "LibTorch headers not found."
  #endif
#else
  #include <torch/torch.h>
  #include <torch/script.h>
#endif

// ============================================================
// 2) Standard headers
// ============================================================
#include <windows.h>
#include <stdio.h>
#include <math.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>

// ============================================================
// 3) Include Stable Archetype Library Common
// ============================================================
#include "include/common/StableArchetypeCommon.hpp"

// ============================================================
// 4) Include Zorro AFTER torch, rename Zorro's 'at'
// ============================================================
#define at zorro_at
#ifdef LOG
#undef LOG
#endif
#include <zorro.h>
#undef at

// ============================================================
// 5) Cleanup macro landmines
// ============================================================
#ifdef min
#undef min
#endif
#ifdef max
#undef max
#endif
#ifdef ref
#undef ref
#endif
#ifdef swap
#undef swap
#endif
#ifdef abs
#undef abs
#endif

// ============================================================
// 6) OpenCL + OpenGL includes
// ============================================================
#include <CL/cl.h>
#include <CL/cl_gl.h>
#include <CL/cl_gl_ext.h>
#include <GL/gl.h>

#ifndef GL_RGBA8
#define GL_RGBA8 0x8058
#endif
#ifndef GL_ARRAY_BUFFER
#define GL_ARRAY_BUFFER 0x8892
#endif
#ifndef GL_PIXEL_UNPACK_BUFFER
#define GL_PIXEL_UNPACK_BUFFER 0x88EC
#endif
#ifndef GL_DYNAMIC_DRAW
#define GL_DYNAMIC_DRAW 0x88E8
#endif

#ifndef APIENTRY
#define APIENTRY __stdcall
#endif
#ifndef APIENTRYP
#define APIENTRYP APIENTRY *
#endif

typedef void (APIENTRYP PFNGLGENBUFFERSPROC)(GLsizei, GLuint*);
typedef void (APIENTRYP PFNGLBINDBUFFERPROC)(GLenum, GLuint);
typedef void (APIENTRYP PFNGLBUFFERDATAPROC)(GLenum, ptrdiff_t, const void*, GLenum);
typedef void (APIENTRYP PFNGLDELETEBUFFERSPROC)(GLsizei, const GLuint*);

static PFNGLGENBUFFERSPROC    p_glGenBuffers    = 0;
static PFNGLBINDBUFFERPROC    p_glBindBuffer    = 0;
static PFNGLBUFFERDATAPROC    p_glBufferData    = 0;
static PFNGLDELETEBUFFERSPROC p_glDeleteBuffers = 0;

static void* gl_get_proc(const char* name)
{
  void* p = (void*)wglGetProcAddress(name);
  if(!p) {
    HMODULE ogl = GetModuleHandleA("opengl32.dll");
    if(ogl) p = (void*)GetProcAddress(ogl, name);
  }
  return p;
}

static int gl_load_ext()
{
  p_glGenBuffers    = (PFNGLGENBUFFERSPROC)gl_get_proc("glGenBuffers");
  p_glBindBuffer    = (PFNGLBINDBUFFERPROC)gl_get_proc("glBindBuffer");
  p_glBufferData    = (PFNGLBUFFERDATAPROC)gl_get_proc("glBufferData");
  p_glDeleteBuffers = (PFNGLDELETEBUFFERSPROC)gl_get_proc("glDeleteBuffers");
  return (p_glGenBuffers && p_glBindBuffer && p_glBufferData && p_glDeleteBuffers) ? 1 : 0;
}

// ============================================================
// Global State
// ============================================================
static HWND   gHwnd = 0;
static HDC    gHdc  = 0;
static HGLRC  gHgl  = 0;

static int    gW = 640;
static int    gH = 480;
static int    gViewportW = 640;
static int    gViewportH = 480;
static float  gPhase = 0.0f;
static unsigned int gNoiseSeed = 1u;

// OpenGL objects
static GLuint gPBO = 0;
static GLuint gTex = 0;

// Context state (Eq 21-30)
struct ContextState {
  float regime;
  float volatility;
  float trend;
  float risk;
};
static ContextState gCtx = {0.0f, 0.0f, 0.0f, 0.0f};
static ContextState gCtxPrev = {0.0f, 0.0f, 0.0f, 0.0f};

// Controller state (Eq 51-60)
static float gArchetypeWeights[K_ARCHETYPES];
static float gTemperature = 1.0f;
static int gSelectedArchetype = 0;

// ============================================================
// LibTorch: Archetype Library (5 archetypes, Eq 1-12)
// ============================================================
#define NN_IN 6
#define NN_H 16
#define NN_OUT 3
#define NN_PARAM_COUNT (NN_H*NN_IN + NN_H + NN_OUT*NN_H + NN_OUT)

static float gHost_W1[K_ARCHETYPES][NN_H*NN_IN];
static float gHost_b1[K_ARCHETYPES][NN_H];
static float gHost_W2[K_ARCHETYPES][NN_OUT*NN_H];
static float gHost_b2[K_ARCHETYPES][NN_OUT];

struct TinyMLPImpl : torch::nn::Module {
  torch::nn::Linear fc1{nullptr}, fc2{nullptr};
  TinyMLPImpl() {
    fc1 = register_module("fc1", torch::nn::Linear(NN_IN, NN_H));
    fc2 = register_module("fc2", torch::nn::Linear(NN_H, NN_OUT));
  }
  torch::Tensor forward(torch::Tensor x) {
    x = torch::tanh(fc1->forward(x));
    x = torch::tanh(fc2->forward(x));
    return x;
  }
};
TORCH_MODULE(TinyMLP);

static int build_archetype_weights(int archetype_id, float* W1, float* b1, float* W2, float* b2)
{
  if(!W1 || !b1 || !W2 || !b2 || archetype_id < 0 || archetype_id >= K_ARCHETYPES) return 0;

  try {
    torch::NoGradGuard ng;
    // Different seed per archetype for diversity (Eq 49)
    torch::manual_seed(42u + (unsigned int)archetype_id * 17u);
    
    TinyMLP m;
    m->eval();

    auto w1  = m->fc1->weight.detach().contiguous().to(torch::kCPU);
    auto bb1 = m->fc1->bias.detach().contiguous().to(torch::kCPU);
    auto w2  = m->fc2->weight.detach().contiguous().to(torch::kCPU);
    auto bb2 = m->fc2->bias.detach().contiguous().to(torch::kCPU);

    memcpy(W1, w1.data_ptr<float>(),  sizeof(float)*NN_H*NN_IN);
    memcpy(b1, bb1.data_ptr<float>(), sizeof(float)*NN_H);
    memcpy(W2, w2.data_ptr<float>(),  sizeof(float)*NN_OUT*NN_H);
    memcpy(b2, bb2.data_ptr<float>(), sizeof(float)*NN_OUT);

    return 1;
  }
  catch(const c10::Error& e) {
    printf("\n[LibTorch] Archetype %d error: %s", archetype_id, e.what());
    return 0;
  }
  catch(...) {
    printf("\n[LibTorch] Archetype %d unknown error", archetype_id);
    return 0;
  }
}

static int init_all_archetypes()
{
  printf("\n[Archetype Library] Initializing %d archetypes...", K_ARCHETYPES);
  const char* names[] = {"order", "turbulence", "growth", "decay", "balance"};
  
  for(int k = 0; k < K_ARCHETYPES; k++) {
    if(!build_archetype_weights(k, gHost_W1[k], gHost_b1[k], gHost_W2[k], gHost_b2[k])) {
      printf("\n[Archetype Library] Failed to init archetype %d (%s)", k, names[k]);
      return 0;
    }
    printf("\n  Archetype %d (%s): W1[%dx%d], b1[%d], W2[%dx%d], b2[%d]",
           k, names[k], NN_H, NN_IN, NN_H, NN_OUT, NN_H, NN_OUT);
  }
  printf("\n[Archetype Library] All archetypes initialized.");
  return 1;
}

// ============================================================
// Context Evolution (CPU, Eq 21-30)
// ============================================================
static float clampf(float x, float lo, float hi)
{
  return (x < lo) ? lo : ((x > hi) ? hi : x);
}

static float sigmoid(float x)
{
  return 1.0f / (1.0f + expf(-x));
}

static unsigned int mix_u32(unsigned int x)
{
  x ^= x >> 16;
  x *= 2246822519u;
  x ^= x >> 13;
  x *= 3266489917u;
  x ^= x >> 16;
  return x;
}

static void evolve_context(float phase, unsigned int seed)
{
  // Save previous context (Eq 60, 85)
  gCtxPrev = gCtx;

  // Hash-based noise (Eq 30, 36, 37, 38)
  unsigned int n = (seed * 26699u + 911u);
  n = (n << 13) ^ n;
  unsigned int m = (n * (n*n*15731u + 789221u) + 1376312589u);
  float noise = ((float)(m & 0x00FFFFFFu) / 16777215.0f) * 2.0f - 1.0f;

  // Regime dynamics with stronger mode transitions
  float regime_raw = 1.20f * sinf(0.19f * phase) + 0.85f * cosf(0.07f * phase) + 0.45f * noise;
  gCtx.regime = tanhf(regime_raw);

  // Volatility with burst behavior
  float burst = 0.5f + 0.5f * sinf(0.43f * phase + 2.7f * gCtx.regime);
  gCtx.volatility = clampf(0.30f + 0.55f * burst + 0.20f * noise, -1.0f, 1.0f);

  // Trend dynamics with long + short waves
  float trend_raw = 0.70f * sinf(0.11f * phase + 1.3f) + 0.35f * cosf(0.51f * phase - 0.6f) + 0.20f * noise;
  gCtx.trend = tanhf(trend_raw);

  // Risk dynamics (Eq 25)
  float risk_raw = 0.9f * gCtx.regime - 0.7f * fabsf(gCtx.volatility) + 0.6f * gCtx.trend + 0.20f * noise;
  gCtx.risk = tanhf(risk_raw);
}

// ============================================================
// Controller (CPU, Eq 51-60)
// ============================================================
static void compute_controller()
{
  // Simple controller: logits from context (Eq 51, 52)
  float logits[K_ARCHETYPES];
  float shock = fabsf(gCtx.volatility - gCtxPrev.volatility);
  float modePulse = 0.5f + 0.5f * sinf(0.37f * gPhase + 3.5f * shock);
  
  // Different archetype preferences based on context
  logits[ARCHE_ORDER]      =  0.8f * gCtx.regime + 0.3f * gCtx.trend - 0.3f * gCtx.volatility;
  logits[ARCHE_TURBULENCE] =  1.1f * gCtx.volatility - 0.2f * gCtx.regime + 0.8f * shock;
  logits[ARCHE_GROWTH]     =  0.9f * gCtx.trend + 0.4f * gCtx.regime + 0.3f * modePulse;
  logits[ARCHE_DECAY]      = -0.9f * gCtx.trend - 0.4f * gCtx.volatility + 0.2f * (1.0f - modePulse);
  logits[ARCHE_BALANCE]    =  0.8f - 0.7f * fabsf(gCtx.regime) - 0.5f * fabsf(gCtx.trend) + 0.4f * (1.0f - shock);

  // Temperature modulation (Eq 56)
  gTemperature = 0.25f + 1.35f * sigmoid(2.2f * gCtx.volatility - 1.8f * shock);

  // Softmax gating (Eq 53)
  float max_logit = logits[0];
  for(int k = 1; k < K_ARCHETYPES; k++) {
    if(logits[k] > max_logit) max_logit = logits[k];
  }

  float sum_exp = 0.0f;
  for(int k = 0; k < K_ARCHETYPES; k++) {
    gArchetypeWeights[k] = expf((logits[k] - max_logit) / gTemperature);
    sum_exp += gArchetypeWeights[k];
  }

  // Normalize (Eq 54, 55)
  for(int k = 0; k < K_ARCHETYPES; k++) {
    gArchetypeWeights[k] /= sum_exp;
  }

  // Find dominant archetype (Eq 57)
  gSelectedArchetype = 0;
  float max_w = gArchetypeWeights[0];
  for(int k = 1; k < K_ARCHETYPES; k++) {
    if(gArchetypeWeights[k] > max_w) {
      max_w = gArchetypeWeights[k];
      gSelectedArchetype = k;
    }
  }
}

// ============================================================
// OpenCL (GL sharing) - GPU Evaluation (Eq 13-100)
// ============================================================
static int gCL_Ready = 0;
static cl_platform_id   gCL_Platform = 0;
static cl_device_id     gCL_Device   = 0;
static cl_context       gCL_Context  = 0;
static cl_command_queue gCL_Queue    = 0;
static cl_program       gCL_Program  = 0;
static cl_kernel        gCL_Kernel   = 0;
static cl_mem           gCL_PBO      = 0;
static cl_mem           gCL_W1[K_ARCHETYPES] = {0};
static cl_mem           gCL_b1[K_ARCHETYPES] = {0};
static cl_mem           gCL_W2[K_ARCHETYPES] = {0};
static cl_mem           gCL_b2[K_ARCHETYPES] = {0};

#define STR2(x) #x
#define XSTR(x) STR2(x)

// OpenCL kernel implementing all 100 equations
static const char* gCL_Source =
"__kernel void render_frame(                                                     \n"
"  __global uchar4* out, int width, int height, float phase, uint seed,          \n"
"  __global const float* W1_0, __global const float* b1_0,                       \n"
"  __global const float* W2_0, __global const float* b2_0,                       \n"
"  __global const float* W1_1, __global const float* b1_1,                       \n"
"  __global const float* W2_1, __global const float* b2_1,                       \n"
"  __global const float* W1_2, __global const float* b1_2,                       \n"
"  __global const float* W2_2, __global const float* b2_2,                       \n"
"  __global const float* W1_3, __global const float* b1_3,                       \n"
"  __global const float* W2_3, __global const float* b2_3,                       \n"
"  __global const float* W1_4, __global const float* b1_4,                       \n"
"  __global const float* W2_4, __global const float* b2_4,                       \n"
"  float pi0, float pi1, float pi2, float pi3, float pi4,                        \n"
"  float ctxRegime, float ctxVol, float ctxTrend, float ctxRisk)                 \n"
"{                                                                               \n"
"  int xpix = (int)get_global_id(0);                                             \n"
"  int ypix = (int)get_global_id(1);                                             \n"
"  if(xpix >= width || ypix >= height) return;                                   \n"
"                                                                                \n"
"  // Eq 14, 15: Normalized coordinates                                        \n"
"  float x = ((float)xpix / (float)(width  - 1)) * 2.0f - 1.0f;                  \n"
"  float y = ((float)ypix / (float)(height - 1)) * 2.0f - 1.0f;                  \n"
"                                                                                \n"
"  // Eq 17: Radial distance                                                    \n"
"  float r = sqrt(x*x + y*y);                                                    \n"
"  float theta = atan2(y, x);                                                     \n"
"  float ring = 0.5f + 0.5f*sin(14.0f*r - 0.9f*phase);                           \n"
"                                                                                \n"
"  // Eq 36, 37, 38: Per-pixel noise                                            \n"
"  uint n = (uint)(xpix*1973u) ^ (uint)(ypix*9277u) ^ (seed*26699u + 911u);      \n"
"  n = (n << 13) ^ n;                                                            \n"
"  uint m = (n * (n*n*15731u + 789221u) + 1376312589u);                          \n"
"  float jitter = ((float)(m & 0x00FFFFFFu) / 16777215.0f) * 2.0f - 1.0f;        \n"
"                                                                                \n"
"  // Eq 32-35: Modulated context inputs                                        \n"
"  float in0 = clamp(0.75f*x + 0.25f*sin(theta + phase), -1.0f, 1.0f);           \n"
"  float in1 = clamp(0.75f*y + 0.25f*cos(theta - phase), -1.0f, 1.0f);           \n"
"  float in2 = clamp(ctxRegime + 0.22f*jitter + 0.20f*sin(phase + 5.0f*r + theta), -1.0f, 1.0f);\n"
"  float in3 = clamp(ctxVol + 0.30f*fabs(jitter) + 0.20f*ring, -1.0f, 1.0f);     \n"
"  float in4 = clamp(ctxTrend + 0.20f*sin(3.0f*x - 2.0f*y + phase) + 0.15f*cos(4.0f*r - theta), -1.0f, 1.0f);\n"
"  float in5 = clamp(ctxRisk + 0.18f*cos(6.0f*theta + 0.5f*phase) - 0.10f*ring, -1.0f, 1.0f);\n"
"                                                                                \n"
"  // Evaluate all 5 archetypes in parallel (Eq 41-50)                          \n"
"  float o[5][3];                                                                \n"
"  for(int arch = 0; arch < 5; arch++) {                                         \n"
"    __global const float* W1 = (arch==0)?W1_0:(arch==1)?W1_1:(arch==2)?W1_2:(arch==3)?W1_3:W1_4;\n"
"    __global const float* b1 = (arch==0)?b1_0:(arch==1)?b1_1:(arch==2)?b1_2:(arch==3)?b1_3:b1_4;\n"
"    __global const float* W2 = (arch==0)?W2_0:(arch==1)?W2_1:(arch==2)?W2_2:(arch==3)?W2_3:W2_4;\n"
"    __global const float* b2 = (arch==0)?b2_0:(arch==1)?b2_1:(arch==2)?b2_2:(arch==3)?b2_3:b2_4;\n"
"                                                                                \n"
"    // Eq 41, 42: First layer with tanh                                        \n"
"    float h[" XSTR(NN_H) "];                                                    \n"
"    for(int j=0;j<" XSTR(NN_H) ";j++) {                                         \n"
"      float acc = b1[j];                                                        \n"
"      acc += in0 * W1[j*" XSTR(NN_IN) " + 0];                                   \n"
"      acc += in1 * W1[j*" XSTR(NN_IN) " + 1];                                   \n"
"      acc += in2 * W1[j*" XSTR(NN_IN) " + 2];                                   \n"
"      acc += in3 * W1[j*" XSTR(NN_IN) " + 3];                                   \n"
"      acc += in4 * W1[j*" XSTR(NN_IN) " + 4];                                   \n"
"      acc += in5 * W1[j*" XSTR(NN_IN) " + 5];                                   \n"
"      h[j] = tanh(acc);                                                         \n"
"    }                                                                           \n"
"                                                                                \n"
"    // Eq 43, 44: Second layer with scaled tanh                                \n"
"    for(int k=0;k<" XSTR(NN_OUT) ";k++) {                                       \n"
"      float acc = b2[k];                                                        \n"
"      for(int j=0;j<" XSTR(NN_H) ";j++) {                                       \n"
"        acc += h[j] * W2[k*" XSTR(NN_H) " + j];                                 \n"
"      }                                                                         \n"
"      float s = 0.5f + 0.5f*tanh(acc);                                          \n"
"      o[arch][k] = (s<0)?0:((s>1)?1:s);                                         \n"
"    }                                                                           \n"
"  }                                                                             \n"
"                                                                                \n"
"  // Eq 61, 62: Blended output                                                 \n"
"  float pi[5] = {pi0, pi1, pi2, pi3, pi4};                                      \n"
"  float blended[3] = {0, 0, 0};                                                 \n"
"  for(int arch=0; arch<5; arch++) {                                             \n"
"    blended[0] += pi[arch] * o[arch][0];                                        \n"
"    blended[1] += pi[arch] * o[arch][1];                                        \n"
"    blended[2] += pi[arch] * o[arch][2];                                        \n"
"  }                                                                             \n"
"  float cross = 0.5f + 0.5f*sin(9.0f*theta + 7.0f*r - 1.3f*phase);              \n"
"  blended[0] = clamp(0.65f*blended[0] + 0.35f*blended[1]*cross, 0.0f, 1.0f);    \n"
"  blended[1] = clamp(0.60f*blended[1] + 0.40f*blended[2]*(1.0f-cross), 0.0f, 1.0f);\n"
"  blended[2] = clamp(0.60f*blended[2] + 0.40f*blended[0]*(0.5f+0.5f*cos(theta+phase)), 0.0f, 1.0f);\n"
"                                                                                \n"
"  // Eq 91-94: Final color synthesis                                           \n"
"  float vignette = clamp(1.20f - r, 0.0f, 1.0f);                                \n"
"  float stripeA = 0.5f + 0.5f*sin(12.0f*(x + y) + phase + 2.5f*jitter);         \n"
"  float stripeB = 0.5f + 0.5f*cos(10.0f*(x - y) - 0.8f*phase);                  \n"
"  float hueMix = clamp(0.5f + 0.35f*ctxRegime + 0.25f*ctxTrend, 0.0f, 1.0f);    \n"
"  float rcol = clamp((0.55f + 0.30f*hueMix)*blended[0] + 0.25f*stripeA + 0.20f*ring, 0.0f, 1.0f) * vignette;\n"
"  float gcol = clamp((0.65f + 0.20f*(1.0f-hueMix))*blended[1] + 0.20f*(1.0f-stripeA) + 0.25f*stripeB, 0.0f, 1.0f) * vignette;\n"
"  float bcol = clamp(0.58f*blended[2] + 0.20f*cross + 0.22f*(0.5f+0.5f*cos(8.0f*theta - phase)), 0.0f, 1.0f);\n"
"                                                                                \n"
"  // Eq 96: 8-bit quantization                                                 \n"
"  uchar redChannel = (uchar)(255.0f*rcol);                                               \n"
"  uchar greenChannel = (uchar)(255.0f*gcol);                                               \n"
"  uchar blueChannel = (uchar)(255.0f*bcol);                                               \n"
"  out[ypix*width + xpix] = (uchar4)(redChannel, greenChannel, blueChannel, 255);                              \n"
"}                                                                               \n";

static void gl_release_all()
{
  const int hasValidWindow = (gHwnd && IsWindow(gHwnd)) ? 1 : 0;
  const int canBindContext = (gHgl && gHdc && hasValidWindow) ? 1 : 0;

  if(canBindContext && wglGetCurrentContext() != gHgl)
    wglMakeCurrent(gHdc, gHgl);

  if(gHgl && wglGetCurrentContext() == gHgl) {
    if(gTex) { glDeleteTextures(1, &gTex); gTex = 0; }
    if(gPBO) { if(p_glDeleteBuffers) p_glDeleteBuffers(1, &gPBO); gPBO = 0; }
  } else {
    gTex = 0;
    gPBO = 0;
  }

  if(gHgl) {
    if(wglGetCurrentContext() == gHgl)
      wglMakeCurrent(NULL, NULL);
    wglDeleteContext(gHgl);
    gHgl = 0;
  }

  if(gHdc && hasValidWindow) ReleaseDC(gHwnd, gHdc);
  gHdc = 0;
}

static void cl_release_all()
{
  for(int k = 0; k < K_ARCHETYPES; k++) {
    if(gCL_b2[k]) { clReleaseMemObject(gCL_b2[k]); gCL_b2[k] = 0; }
    if(gCL_W2[k]) { clReleaseMemObject(gCL_W2[k]); gCL_W2[k] = 0; }
    if(gCL_b1[k]) { clReleaseMemObject(gCL_b1[k]); gCL_b1[k] = 0; }
    if(gCL_W1[k]) { clReleaseMemObject(gCL_W1[k]); gCL_W1[k] = 0; }
  }
  if(gCL_PBO)     { clReleaseMemObject(gCL_PBO); gCL_PBO = 0; }
  if(gCL_Kernel)  { clReleaseKernel(gCL_Kernel); gCL_Kernel = 0; }
  if(gCL_Program) { clReleaseProgram(gCL_Program); gCL_Program = 0; }
  if(gCL_Queue)   { clReleaseCommandQueue(gCL_Queue); gCL_Queue = 0; }
  if(gCL_Context) { clReleaseContext(gCL_Context); gCL_Context = 0; }
  gCL_Device = 0; gCL_Platform = 0; gCL_Ready = 0;
}

static int cl_pick_device_with_glshare(cl_platform_id* outP, cl_device_id* outD)
{
  cl_uint nPlatforms = 0;
  if(clGetPlatformIDs(0, 0, &nPlatforms) != CL_SUCCESS || nPlatforms == 0) return 0;

  cl_platform_id platforms[8];
  if(nPlatforms > 8) nPlatforms = 8;
  if(clGetPlatformIDs(nPlatforms, platforms, &nPlatforms) != CL_SUCCESS) return 0;

  for(cl_uint p = 0; p < nPlatforms; p++) {
    cl_uint nDev = 0;
    if(clGetDeviceIDs(platforms[p], CL_DEVICE_TYPE_GPU, 0, 0, &nDev) != CL_SUCCESS || nDev == 0) continue;

    cl_device_id devs[8];
    if(nDev > 8) nDev = 8;
    if(clGetDeviceIDs(platforms[p], CL_DEVICE_TYPE_GPU, nDev, devs, &nDev) != CL_SUCCESS) continue;

    for(cl_uint d = 0; d < nDev; d++) {
      char ext[8192];
      if(clGetDeviceInfo(devs[d], CL_DEVICE_EXTENSIONS, sizeof(ext), ext, 0) != CL_SUCCESS) continue;
      if(strstr(ext, "cl_khr_gl_sharing")) {
        *outP = platforms[p];
        *outD = devs[d];
        return 1;
      }
    }
  }
  return 0;
}

static int cl_init_glshare()
{
  cl_int err = CL_SUCCESS;
  cl_platform_id P = 0;
  cl_device_id D = 0;

  if(!cl_pick_device_with_glshare(&P, &D)) {
    printf("\nOpenCL: no GPU with cl_khr_gl_sharing found.");
    return 0;
  }

  gCL_Platform = P; gCL_Device = D;

  cl_context_properties props[] = {
    CL_GL_CONTEXT_KHR,   (cl_context_properties)wglGetCurrentContext(),
    CL_WGL_HDC_KHR,      (cl_context_properties)wglGetCurrentDC(),
    CL_CONTEXT_PLATFORM, (cl_context_properties)gCL_Platform,
    0
  };

  gCL_Context = clCreateContext(props, 1, &gCL_Device, 0, 0, &err);
  if(err != CL_SUCCESS || !gCL_Context) { cl_release_all(); return 0; }

  gCL_Queue = clCreateCommandQueue(gCL_Context, gCL_Device, 0, &err);
  if(err != CL_SUCCESS || !gCL_Queue) { cl_release_all(); return 0; }

  gCL_Program = clCreateProgramWithSource(gCL_Context, 1, &gCL_Source, 0, &err);
  if(err != CL_SUCCESS || !gCL_Program) { cl_release_all(); return 0; }

  err = clBuildProgram(gCL_Program, 1, &gCL_Device, 0, 0, 0);
  if(err != CL_SUCCESS) {
    char logbuf[8192];
    clGetProgramBuildInfo(gCL_Program, gCL_Device, CL_PROGRAM_BUILD_LOG, sizeof(logbuf), logbuf, 0);
    printf("\nOpenCL build failed:\n%s", logbuf);
    cl_release_all(); return 0;
  }

  gCL_Kernel = clCreateKernel(gCL_Program, "render_frame", &err);
  if(err != CL_SUCCESS || !gCL_Kernel) { cl_release_all(); return 0; }

  gCL_PBO = clCreateFromGLBuffer(gCL_Context, CL_MEM_WRITE_ONLY, gPBO, &err);
  if(err != CL_SUCCESS || !gCL_PBO) { cl_release_all(); return 0; }

  size_t bytesW1 = sizeof(float)*NN_H*NN_IN;
  size_t bytesb1 = sizeof(float)*NN_H;
  size_t bytesW2 = sizeof(float)*NN_OUT*NN_H;
  size_t bytesb2 = sizeof(float)*NN_OUT;

  for(int k = 0; k < K_ARCHETYPES; k++) {
    gCL_W1[k] = clCreateBuffer(gCL_Context, CL_MEM_READ_ONLY, bytesW1, 0, &err);
    gCL_b1[k] = clCreateBuffer(gCL_Context, CL_MEM_READ_ONLY, bytesb1, 0, &err);
    gCL_W2[k] = clCreateBuffer(gCL_Context, CL_MEM_READ_ONLY, bytesW2, 0, &err);
    gCL_b2[k] = clCreateBuffer(gCL_Context, CL_MEM_READ_ONLY, bytesb2, 0, &err);
    if(err != CL_SUCCESS) { cl_release_all(); return 0; }
  }

  for(int k = 0; k < K_ARCHETYPES; k++) {
    err = clEnqueueWriteBuffer(gCL_Queue, gCL_W1[k], CL_TRUE, 0, bytesW1, gHost_W1[k], 0, 0, 0);
    if(err != CL_SUCCESS) { cl_release_all(); return 0; }
    err = clEnqueueWriteBuffer(gCL_Queue, gCL_b1[k], CL_TRUE, 0, bytesb1, gHost_b1[k], 0, 0, 0);
    if(err != CL_SUCCESS) { cl_release_all(); return 0; }
    err = clEnqueueWriteBuffer(gCL_Queue, gCL_W2[k], CL_TRUE, 0, bytesW2, gHost_W2[k], 0, 0, 0);
    if(err != CL_SUCCESS) { cl_release_all(); return 0; }
    err = clEnqueueWriteBuffer(gCL_Queue, gCL_b2[k], CL_TRUE, 0, bytesb2, gHost_b2[k], 0, 0, 0);
    if(err != CL_SUCCESS) { cl_release_all(); return 0; }
  }

  gCL_Ready = 1;
  return 1;
}

static int gl_init_wgl(HWND hwnd)
{
  gHwnd = hwnd;
  gHdc = GetDC(hwnd);
  if(!gHdc) return 0;

  PIXELFORMATDESCRIPTOR pfd;
  ZeroMemory(&pfd, sizeof(pfd));
  pfd.nSize = sizeof(pfd);
  pfd.nVersion = 1;
  pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
  pfd.iPixelType = PFD_TYPE_RGBA;
  pfd.cColorBits = 32;
  pfd.cDepthBits = 16;
  pfd.iLayerType = PFD_MAIN_PLANE;

  int pf = ChoosePixelFormat(gHdc, &pfd);
  if(pf == 0) return 0;
  if(!SetPixelFormat(gHdc, pf, &pfd)) return 0;

  gHgl = wglCreateContext(gHdc);
  if(!gHgl) return 0;
  if(!wglMakeCurrent(gHdc, gHgl)) return 0;

  if(!gl_load_ext()) {
    printf("\nOpenGL buffer functions not available.");
    return 0;
  }

  glClearColor(0.f, 0.f, 0.f, 1.f);
  glDisable(GL_DEPTH_TEST);
  glViewport(0, 0, gW, gH);

  // Create PBO (Eq 97)
  p_glGenBuffers(1, &gPBO);
  p_glBindBuffer(GL_PIXEL_UNPACK_BUFFER, gPBO);
  p_glBufferData(GL_PIXEL_UNPACK_BUFFER, (ptrdiff_t)(gW * gH * 4), 0, GL_DYNAMIC_DRAW);
  p_glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);

  // Create texture
  glGenTextures(1, &gTex);
  glBindTexture(GL_TEXTURE_2D, gTex);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, gW, gH, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
  glBindTexture(GL_TEXTURE_2D, 0);

  return 1;
}

// ============================================================
// Render Frame (GPU)
// ============================================================
static void render_frame_gpu()
{
  if(!gCL_Ready) return;

  // Acquire PBO (Eq 97)
  cl_int err = clEnqueueAcquireGLObjects(gCL_Queue, 1, &gCL_PBO, 0, 0, 0);
  if(err != CL_SUCCESS) {
    static int sLoggedAcquireError = 0;
    if(!sLoggedAcquireError) {
      printf("\n[OpenCL] clEnqueueAcquireGLObjects failed: %d", (int)err);
      sLoggedAcquireError = 1;
    }
    return;
  }

  // Set kernel arguments
  int arg = 0;
  clSetKernelArg(gCL_Kernel, arg++, sizeof(cl_mem), &gCL_PBO);
  clSetKernelArg(gCL_Kernel, arg++, sizeof(int), &gW);
  clSetKernelArg(gCL_Kernel, arg++, sizeof(int), &gH);
  clSetKernelArg(gCL_Kernel, arg++, sizeof(float), &gPhase);
  clSetKernelArg(gCL_Kernel, arg++, sizeof(unsigned int), &gNoiseSeed);
  
  // Archetype 0
  clSetKernelArg(gCL_Kernel, arg++, sizeof(cl_mem), &gCL_W1[0]);
  clSetKernelArg(gCL_Kernel, arg++, sizeof(cl_mem), &gCL_b1[0]);
  clSetKernelArg(gCL_Kernel, arg++, sizeof(cl_mem), &gCL_W2[0]);
  clSetKernelArg(gCL_Kernel, arg++, sizeof(cl_mem), &gCL_b2[0]);
  // Archetype 1
  clSetKernelArg(gCL_Kernel, arg++, sizeof(cl_mem), &gCL_W1[1]);
  clSetKernelArg(gCL_Kernel, arg++, sizeof(cl_mem), &gCL_b1[1]);
  clSetKernelArg(gCL_Kernel, arg++, sizeof(cl_mem), &gCL_W2[1]);
  clSetKernelArg(gCL_Kernel, arg++, sizeof(cl_mem), &gCL_b2[1]);
  // Archetype 2
  clSetKernelArg(gCL_Kernel, arg++, sizeof(cl_mem), &gCL_W1[2]);
  clSetKernelArg(gCL_Kernel, arg++, sizeof(cl_mem), &gCL_b1[2]);
  clSetKernelArg(gCL_Kernel, arg++, sizeof(cl_mem), &gCL_W2[2]);
  clSetKernelArg(gCL_Kernel, arg++, sizeof(cl_mem), &gCL_b2[2]);
  // Archetype 3
  clSetKernelArg(gCL_Kernel, arg++, sizeof(cl_mem), &gCL_W1[3]);
  clSetKernelArg(gCL_Kernel, arg++, sizeof(cl_mem), &gCL_b1[3]);
  clSetKernelArg(gCL_Kernel, arg++, sizeof(cl_mem), &gCL_W2[3]);
  clSetKernelArg(gCL_Kernel, arg++, sizeof(cl_mem), &gCL_b2[3]);
  // Archetype 4
  clSetKernelArg(gCL_Kernel, arg++, sizeof(cl_mem), &gCL_W1[4]);
  clSetKernelArg(gCL_Kernel, arg++, sizeof(cl_mem), &gCL_b1[4]);
  clSetKernelArg(gCL_Kernel, arg++, sizeof(cl_mem), &gCL_W2[4]);
  clSetKernelArg(gCL_Kernel, arg++, sizeof(cl_mem), &gCL_b2[4]);
  
  // Archetype weights (Eq 53)
  clSetKernelArg(gCL_Kernel, arg++, sizeof(float), &gArchetypeWeights[0]);
  clSetKernelArg(gCL_Kernel, arg++, sizeof(float), &gArchetypeWeights[1]);
  clSetKernelArg(gCL_Kernel, arg++, sizeof(float), &gArchetypeWeights[2]);
  clSetKernelArg(gCL_Kernel, arg++, sizeof(float), &gArchetypeWeights[3]);
  clSetKernelArg(gCL_Kernel, arg++, sizeof(float), &gArchetypeWeights[4]);
  
  // Context (Eq 21)
  clSetKernelArg(gCL_Kernel, arg++, sizeof(float), &gCtx.regime);
  clSetKernelArg(gCL_Kernel, arg++, sizeof(float), &gCtx.volatility);
  clSetKernelArg(gCL_Kernel, arg++, sizeof(float), &gCtx.trend);
  clSetKernelArg(gCL_Kernel, arg++, sizeof(float), &gCtx.risk);

  // Execute kernel (Eq 13-100, all pixels in parallel)
  size_t global[2] = {(size_t)gW, (size_t)gH};
  err = clEnqueueNDRangeKernel(gCL_Queue, gCL_Kernel, 2, 0, global, 0, 0, 0, 0);
  if(err != CL_SUCCESS) {
    static int sLoggedKernelError = 0;
    if(!sLoggedKernelError) {
      printf("\n[OpenCL] clEnqueueNDRangeKernel failed: %d", (int)err);
      sLoggedKernelError = 1;
    }
    clEnqueueReleaseGLObjects(gCL_Queue, 1, &gCL_PBO, 0, 0, 0);
    clFinish(gCL_Queue);
    return;
  }
  
  // Check for kernel execution errors
  clFinish(gCL_Queue);

  // Release PBO
  clEnqueueReleaseGLObjects(gCL_Queue, 1, &gCL_PBO, 0, 0, 0);
  clFinish(gCL_Queue);

  // Update texture from PBO (Eq 98)
  p_glBindBuffer(GL_PIXEL_UNPACK_BUFFER, gPBO);
  glBindTexture(GL_TEXTURE_2D, gTex);
  glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, gW, gH, GL_RGBA, GL_UNSIGNED_BYTE, 0);
  p_glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);
}

// ============================================================
// Display (OpenGL, Eq 99)
// ============================================================
static void display()
{
  if(!gHdc || !gTex) return;
  glViewport(0, 0, gViewportW, gViewportH);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
  
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, gTex);
  
  glBegin(GL_QUADS);
  glTexCoord2f(0, 0); glVertex2f(-1, -1);
  glTexCoord2f(1, 0); glVertex2f( 1, -1);
  glTexCoord2f(1, 1); glVertex2f( 1,  1);
  glTexCoord2f(0, 1); glVertex2f(-1,  1);
  glEnd();
  
  glDisable(GL_TEXTURE_2D);
  SwapBuffers(gHdc);
}

// ============================================================
// Window Procedure
// ============================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
  switch(msg) {
    case WM_CLOSE:
      DestroyWindow(hWnd);
      return 0;
    case WM_SIZE:
      gViewportW = LOWORD(lParam);
      gViewportH = HIWORD(lParam);
      if(gViewportW < 1) gViewportW = 1;
      if(gViewportH < 1) gViewportH = 1;
      if(gHgl && wglGetCurrentContext() == gHgl)
        glViewport(0, 0, gViewportW, gViewportH);
      return 0;
    case WM_DESTROY:
      PostQuitMessage(0);
      return 0;
    case WM_KEYDOWN:
      if(wParam == VK_ESCAPE) {
        PostMessage(hWnd, WM_CLOSE, 0, 0);
      }
      return 0;
  }
  return DefWindowProc(hWnd, msg, wParam, lParam);
}

// ============================================================
// Main Entry Point (Zorro DLL)
// ============================================================
DLLFUNC int main()
{
  try {
  NumTotalCycles = 1;
  NumWFOCycles = 1;
  NumSampleCycles = 1;
  set(TESTNOW|OFF, ALLCYCLES|OFF, PARAMETERS|OFF, FACTORS|OFF, RULES|OFF);

  static int done = 0;
  if(is(FIRSTINITRUN) || is(INITRUN) || Bar == 0)
    done = 0;

  if(done)
    return 0;

  printf("\n\n========================================");
  printf("\n Mendb11 - Stable Archetype Library");
  printf("\n 100-Equation Modular GPU Framework");
  printf("\n========================================");
  printf("\n [Eq 1-12]   Archetype Library: %d archetypes", K_ARCHETYPES);
  printf("\n [Eq 13-20]  Spatial Geometry");
  printf("\n [Eq 21-30]  Context Evolution");
  printf("\n [Eq 31-40]  Pixel Input Synthesis");
  printf("\n [Eq 41-50]  Archetype Neural Evaluation");
  printf("\n [Eq 51-60]  Controller/Gating");
  printf("\n [Eq 61-70]  Blending");
  printf("\n [Eq 71-80]  Semantic Diagnostics");
  printf("\n [Eq 81-90]  Temporal Diagnostics");
  printf("\n [Eq 91-100] Final Color Synthesis");
  printf("\n========================================");

  // Initialize archetypes with LibTorch (Eq 1-12, CPU)
  if(!init_all_archetypes()) {
    printf("\nFailed to initialize archetypes.");
    return quit("!Mendb11: archetype init failed");
  }

  // Create window
  HINSTANCE hInst = GetModuleHandleA(NULL);
  const char* wndClassName = "Mendb11Class";
  UnregisterClassA(wndClassName, hInst);

  WNDCLASSEXA wc;
  ZeroMemory(&wc, sizeof(wc));
  wc.cbSize = sizeof(wc);
  wc.style = CS_HREDRAW | CS_VREDRAW;
  wc.lpfnWndProc = WndProc;
  wc.hInstance = hInst;
  wc.hCursor = LoadCursor(NULL, IDC_ARROW);
  wc.lpszClassName = wndClassName;

  if(!RegisterClassExA(&wc)) {
    printf("\nFailed to register window class. GetLastError=%lu", (unsigned long)GetLastError());
    return quit("!Mendb11: window class registration failed");
  }

  HWND hwnd = CreateWindowEx(0, "Mendb11Class", "Mendb11 - Stable Archetype Library (100 Equations)",
                             WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, gW+200, gH+200,
                             0, 0, hInst, 0);
  if(!hwnd) {
    printf("\nFailed to create window.");
    return quit("!Mendb11: window creation failed");
  }

  // Initialize OpenGL (Eq 97-99)
  if(!gl_init_wgl(hwnd)) {
    printf("\nOpenGL init failed.");
    if(hwnd && IsWindow(hwnd)) DestroyWindow(hwnd);
    return quit("!Mendb11: OpenGL init failed");
  }
  printf("\n[OpenGL] Initialized with PBO (Eq 97)");

  // Initialize OpenCL with GL sharing (Eq 13-100)
  if(!cl_init_glshare()) {
    printf("\nOpenCL init failed.");
    gl_release_all();
    if(hwnd && IsWindow(hwnd)) DestroyWindow(hwnd);
    return quit("!Mendb11: OpenCL init failed");
  }
  printf("\n[OpenCL] GPU compute initialized with GL sharing");
  printf("\n[Pipeline] c_t -> pi(t) -> o_{k,p,t} -> o_{p,t} -> I_{p,t}");

  ShowWindow(hwnd, SW_SHOW);
  UpdateWindow(hwnd);
  // Initial viewport set in WM_SIZE handler
  // Set initial viewport to match window client area
  RECT clientRect;
  GetClientRect(hwnd, &clientRect);
  gViewportW = clientRect.right;
  gViewportH = clientRect.bottom;
  if(gViewportW < 1) gViewportW = 1;
  if(gViewportH < 1) gViewportH = 1;
  glViewport(0, 0, gViewportW, gViewportH);
  UpdateWindow(hwnd);
  // Initial viewport set in WM_SIZE handler

  // Main render loop
  MSG msg = {0};
  int frame = 0;
  DWORD lastTime = GetTickCount();

  printf("\n[Render] Starting GPU render loop...");

  while(msg.message != WM_QUIT) {
    while(PeekMessage(&msg, 0, 0, 0, PM_REMOVE)) {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }

    if(!IsWindow(hwnd))
      break;

    // Evolve context (Eq 21-30, CPU)
    evolve_context(gPhase, gNoiseSeed);
    
    // Compute controller (Eq 51-60, CPU)
    compute_controller();

    // Render frame (Eq 13-100, GPU)
    render_frame_gpu();
    
    // Display (Eq 99, GPU)
    display();

    // Advance phase
    // Handle window resize dynamically
    gPhase += 0.015f;
    gNoiseSeed = mix_u32(gNoiseSeed);
    frame++;

    // Status every 60 frames
    if(frame % 60 == 0) {
      DWORD now = GetTickCount();
      float fps = 60000.0f / (float)(now - lastTime + 1);
      printf("\n[Frame %d] FPS: %.1f, Context: [%.2f, %.2f, %.2f, %.2f], Dominant: %d",
             frame, fps, gCtx.regime, gCtx.volatility, gCtx.trend, gCtx.risk, gSelectedArchetype);
      lastTime = now;
    }

    // Poll STOP
    if(is(EXITRUN) && !is(FIRSTINITRUN)) {
      PostMessage(hwnd, WM_CLOSE, 0, 0);
    }
  }

  // Cleanup: release OpenCL-GL shared objects first, then GL context/window
  printf("\n[Shutdown] Begin cleanup");
  if(gCL_Queue) clFinish(gCL_Queue);
  printf("\n[Shutdown] Releasing OpenCL");
  cl_release_all();
  printf("\n[Shutdown] Releasing OpenGL");
  gl_release_all();
  if(hwnd && IsWindow(hwnd)) {
    printf("\n[Shutdown] Destroying window");
    DestroyWindow(hwnd);
  }

  gHwnd = 0;
  done = 1;

  printf("\n[Mendb11] Shutdown complete.");
  return 0;
  }
  catch(const c10::Error& e) {
    printf("\n[Mendb11] c10 exception in main: %s", e.what());
    return 0;
  }
  catch(const std::exception& e) {
    printf("\n[Mendb11] std exception in main: %s", e.what());
    return 0;
  }
  catch(...) {
    printf("\n[Mendb11] unknown exception in main");
    return 0;
  }
}
