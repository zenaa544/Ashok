1. Power On
Location: Physical hardware (Motherboard, CPU, RAM, storage, power supply)
How Loaded: Power button pressed, electrical flow begins
What Happens:
CPU resets
Begins execution from the reset vector in ROM
2. BIOS/UEFI Firmware
Location: EEPROM or flash chip on motherboard (not disk/RAM)
How Loaded: CPU executes instructions stored in firmware at reset vector
What Happens:
POST (Power-On Self Test) runs
Hardware initialized (CPU, memory, video, keyboard, storage controller)
Boot device identified (from BIOS/UEFI setup)
3. Bootloader (MBR or EFI Partition)
Location:
BIOS: MBR – first 512 bytes of boot disk
UEFI: EFI System Partition (FAT), e.g. /EFI/BOOT/BOOTX64.EFI
How Loaded:
BIOS reads MBR from disk, loads to RAM, jumps to code
UEFI reads EFI file from disk, loads to RAM, hands control
What Happens:
Bootloader (e.g. GRUB) code runs in RAM
Prepares to load OS (kernel/initramfs)
4. Bootloader Execution
Location: Bootloader now in RAM
How Loaded: Started by BIOS/UEFI
What Happens:
Boot menu presented
Loads Linux kernel and initramfs/initrd files into RAM
Sets kernel parameters
Transfers control to kernel entry point
5. Kernel Initialization
Location: Kernel image (/boot/vmlinuz) on disk, now running from RAM
How Loaded: Loaded by bootloader
What Happens:
Kernel decompresses
Sets up virtual memory/page tables
Initializes hardware/drivers
Loads/initramfs or initrd image
6. Initramfs/initrd (Early Userspace)
Location: Initramfs/initrd file on disk, now in RAM
How Loaded: Loaded by bootloader
What Happens:
Kernel mounts as temporary root filesystem
Runs scripts/tools for early boot tasks (RAID, LVM, decryption)
Loads essential drivers/modules
7. Mount Root Filesystem
Location: Disk partition (SSD/HDD) mounted as /
How Loaded: Kernel uses initramfs tools/scripts
What Happens:
Kernel mounts actual root filesystem
Switches root from RAM (initramfs) to disk (real root)
8. Init/Systemd (First User-space Process)
Location: Binary (/sbin/init or /lib/systemd/systemd) on root filesystem
How Loaded: Kernel starts this as PID 1
What Happens:
Reads config files (/etc/inittab, systemd units)
Launches system services, targets, mounts
9. Services/Daemons/Targets
Location: Executables/scripts on root filesystem
How Loaded: Started by init/systemd
What Happens:
Launches background services (network, logging, device management)
Establishes runlevel/target (multi-user, graphical)
10. Login Prompt/Desktop
Location: Console getty/display manager binary on root filesystem
How Loaded: Started as a service
What Happens:
Presents login prompt (text or GUI)
User authentication leads to shell or desktop session


| Step | Stage                | Where It Resides            | How It Gets Loaded/Executed              | What Happens                                                      |
|------|----------------------|-----------------------------|------------------------------------------|-------------------------------------------------------------------|
| 1    | Power On             | Hardware                    | Electrical power flows                   | CPU resets, fetches instruction from ROM (reset vector)           |
| 2    | BIOS/UEFI Firmware   | Motherboard firmware chip   | CPU runs from reset vector               | POST, hardware initialization, finds boot device                  |
| 3    | Bootloader           | Disk (MBR/EFI partition)    | BIOS/UEFI loads into RAM                 | Bootloader code runs, prepares to boot OS                         |
| 4    | Bootloader Execution | RAM (loaded from disk)      | BIOS/UEFI jumps to RAM address           | Loads kernel/initramfs, sets options, passes control to kernel    |
| 5    | Kernel               | Disk, then RAM              | Bootloader loads kernel image to RAM     | Kernel decompresses, hardware/drivers init, memory setup          |
| 6    | Initramfs/initrd     | Disk, then RAM              | Bootloader loads, kernel mounts as root  | Early userspace, loads drivers, mounts real root                  |
| 7    | Root Filesystem      | Disk/SSD (root partition)   | Initramfs/initrd scripts, kernel         | Real root filesystem mounted, switch to disk-based root           |
| 8    | Init/Systemd         | Root filesystem             | Kernel starts as PID 1                   | Reads config, launches services, completes boot                   |
| 9    | Services/Daemons     | Root filesystem             | Init/systemd launches processes          | Networking, logging, device management, user-space processes      |
| 10   | Login Prompt/Desktop | Root filesystem             | getty/display manager starts             | User login – shell or desktop session provided                    |
