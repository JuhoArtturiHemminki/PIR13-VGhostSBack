#ifndef PIR13_CORE_H
#define PIR13_CORE_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define PIR13_CACHE_LINE 128
#define PIR13_MAE_WINDOW_BYTES 16384
#define PIR13_1BIT_ELEMENTS (PIR13_MAE_WINDOW_BYTES * 8)

typedef struct {
    uint64_t exponent_n;
} pir13_slqr_time_t;

typedef struct {
    uint64_t solidnorm2_vector[2];
    uint8_t mae_buffer[PIR13_MAE_WINDOW_BYTES];
    pir13_slqr_time_t zeno_time;
    uint64_t left_boundary;
    uint64_t right_boundary;
} pir13_compute_node_t;

void* pir13_platform_create(size_t gigabytes);
void pir13_platform_process(void* platform_ptr);
double pir13_platform_get_latency(void* platform_ptr);
double pir13_platform_get_gflops(void* platform_ptr);
void pir13_platform_run_diagnostics(void* platform_ptr);
void pir13_platform_destroy(void* platform_ptr);

#ifdef __cplusplus
}
#endif

#endif
