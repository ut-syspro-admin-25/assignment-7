#include <efi.h>
#include <memory.h>
#include <util.h>

#define MEMMAP_BUFFER_SIZE 128 // Arbitrary size
struct EFI_MEMORY_DESCRIPTOR memmap_buffer[MEMMAP_BUFFER_SIZE];
UINTN mmap_size;
UINTN descsize;

void exit_boot_services(EFI_HANDLE ImageHandle) {
  EFI_STATUS status;

  mmap_size = MEMMAP_BUFFER_SIZE * sizeof(struct EFI_MEMORY_DESCRIPTOR);
  UINTN map_key;
  UINT32 descriptor_version;
  status = SystemTable->BootServices->GetMemoryMap(
      &mmap_size, memmap_buffer, &map_key, &descsize, &descriptor_version);
  assert(status, L"GetMemoryMap");

  status = SystemTable->BootServices->ExitBootServices(ImageHandle, map_key);
  assert(status, L"BootServices#ExitBootServices");
}
