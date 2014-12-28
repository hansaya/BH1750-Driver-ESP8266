rmdir /s /q "J:\VMs\share\smartmeter\build"

python flash.py --port COM10 write_flash 0x00000 firmware/0x00000.bin