CC=arm-none-eabi-
CFLAGS= -mcpu=cortex-m3 -mthumb -gdwarf-2
INCS= -I .
SRC= $(wildcard *.c)
OBJ= $(SRC:.c=.o)
all: learn-in-depth_cortexM3.hex
	@echo "-----DONE-----"

%.o: %.c
	$(CC)gcc.exe $(CFLAGS) $(INCS) -c $< -o $@

learn-in-depth.elf: $(OBJ) 
	$(CC)ld.exe -T linker_script.ld $(OBJ) -o $@ -Map=Map_file.map

learn-in-depth_cortexM3.hex: learn-in-depth.elf
	$(CC)objcopy.exe -O binary $< $@

clean: 
	rm *.o *.elf *.hex
	@echo "----CLEAN_ALL----"


