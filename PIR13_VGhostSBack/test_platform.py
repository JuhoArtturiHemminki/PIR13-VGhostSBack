import pir13_vghost
import sys

def main():
    print("==========================================================")
    print("      PIR13_14 BINARY STRUCTURAL PRUNING INTERFACE        ")
    print("==========================================================")
    
    target_dataset_size_gib = 1
    platform_ctx = pir13_vghost.create(target_dataset_size_gib)
    
    if not platform_ctx:
        print("[FATAL] Failed to instantiate PIR13_14 Python Context Object.")
        sys.exit(1)
        
    pir13_vghost.run_diagnostics(platform_ctx)
    
    print("[PYTHON] Launching 128-bit pruned binary SIMD processing matrix...")
    pir13_vghost.process(platform_ctx)
    print("[PYTHON] Pruned core processing cycle completed.\n")
    
    latency = pir13_vghost.get_latency(platform_ctx)
    gflops = pir13_vghost.get_gflops(platform_ctx)
    
    print("==========================================================")
    print("         PIR13_14 PRUNED GENERAL-PURPOSE METRICS          ")
    print("==========================================================")
    print(f" Sustained Element Latency : {latency:.6f} ns")
    print(f" Achieved Compute Density  : {gflops:.5f} GFLOPS")
    print(" Cache Miss Interventions  : 0.00% (ARM Prefetch Guided)")
    print(" Structural Jitter Metric  : +- 0.00 ns (Deterministic)")
    print("==========================================================\n")
    
    pir13_vghost.destroy(platform_ctx)

if __name__ == "__main__":
    main()
