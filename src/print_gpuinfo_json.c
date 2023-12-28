#include <stdio.h>

#include "nvtop/interface.h"
#include "nvtop/print_gpuinfo_json.h"

void print_gpuinfo_json(struct list_head *monitoredGpus) {
  struct gpu_info *device;

  gpuinfo_refresh_dynamic_info(monitoredGpus);
  gpuinfo_refresh_processes(monitoredGpus);
  gpuinfo_utilisation_rate(monitoredGpus);
  gpuinfo_fix_dynamic_info_from_process_info(monitoredGpus);

  printf("[\n");
  list_for_each_entry(device, monitoredGpus, list) {
    printf("  {\n");
    printf("    \"device_name\": \"%s\",\n", device->static_info.device_name);
    printf("    \"gpu_clock_speed\": %u,\n", device->dynamic_info.gpu_clock_speed);
    printf("    \"gpu_clock_speed_max\": %u,\n", device->dynamic_info.gpu_clock_speed_max);
    printf("    \"mem_clock_speed\": %u,\n", device->dynamic_info.mem_clock_speed);
    printf("    \"mem_clock_speed_max\": %u,\n", device->dynamic_info.mem_clock_speed_max);
    printf("    \"gpu_util_rate\": %u,\n", device->dynamic_info.gpu_util_rate);
    printf("    \"mem_util_rate\": %u,\n", device->dynamic_info.mem_util_rate);
    printf("    \"encoder_rate\": %u,\n", device->dynamic_info.encoder_rate);
    printf("    \"decoder_rate\": %u,\n", device->dynamic_info.decoder_rate);
    printf("    \"total_memory\": %llu,\n", device->dynamic_info.total_memory);
    printf("    \"free_memory\": %llu,\n", device->dynamic_info.free_memory);
    printf("    \"used_memory\": %llu,\n", device->dynamic_info.used_memory);
    printf("    \"pcie_link_gen\": %u,\n", device->dynamic_info.pcie_link_gen);
    printf("    \"pcie_link_width\": %u,\n", device->dynamic_info.pcie_link_width);
    printf("    \"pcie_rx\": %u,\n", device->dynamic_info.pcie_rx);
    printf("    \"pcie_tx\": %u,\n", device->dynamic_info.pcie_tx);
    printf("    \"fan_speed\": %u,\n", device->dynamic_info.fan_speed);
    printf("    \"gpu_temp\": %u,\n", device->dynamic_info.gpu_temp);
    printf("    \"power_draw\": %u,\n", device->dynamic_info.power_draw);
    printf("    \"power_draw_max\": %u,\n", device->dynamic_info.power_draw_max);
    printf("    \"encode_decode_shared\": %u\n", device->dynamic_info.encode_decode_shared);
    printf("  }");
    if (device->list.next != monitoredGpus) {
      printf(",\n");
    } else {
      printf("\n");
    }
  }
  printf("]\n");
}
