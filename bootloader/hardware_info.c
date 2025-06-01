#include <efi.h>
#include <hardware_info.h>
#include <memory.h>
#include <util.h>

struct HardwareInfo hardware_info;

#define MEMMAP_BUFFER_SIZE 128 // Arbitrary size
extern char memmap_buffer[];
extern UINTN mmap_size;
extern UINTN descsize;

void get_hardware_info() {
  int nmap = 0;

  hardware_info.fb.base = (struct Pixel *)GOP->Mode->FrameBufferBase;
  hardware_info.fb.width = GOP->Mode->Info->HorizontalResolution;
  hardware_info.fb.height = GOP->Mode->Info->VerticalResolution;
  hardware_info.fb.total_size = GOP->Mode->FrameBufferSize;

  hardware_info.rsdp = find_acpi_table();

  /*
  puts (L"descsize ");
  puth (descsize, 16);
  puts (L"mmap size ");
  puth (mmap_size, 16);
  puts (L"base ");
  puth (memmap_buffer, 16);
  puts (L"\r\n ");
  */
  for (UINTN i = 0; i < mmap_size / descsize; i++) {
    struct EFI_MEMORY_DESCRIPTOR *memmap = memmap_buffer + i * descsize;
    if (memmap->Type == 7) {
      struct AvailMemoryMap *mm = &hardware_info.memmap[nmap++];
      mm->type = memmap->Type;
      mm->base_addr = memmap->PhysicalStart;
      mm->size = memmap->NumberOfPages * 0x1000;
      /*
      puts (L"MM type ");
      puth (mm->type, 16);
      puts (L"base addr ");
      puth (mm->base_addr, 16);
      puts (L"size ");
      puth (mm->size, 16);
      puts (L"\r\n");
      */
    }
  }

  hardware_info.nmemmap = nmap;
}

EFI_GRAPHICS_PIXEL_FORMAT get_pixel_format() {
  return GOP->Mode->Info->PixelFormat;
}
