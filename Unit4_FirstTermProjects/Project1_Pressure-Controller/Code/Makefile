CC=arm-none-eabi-
CFLAGS= -mcpu=cortex-m3 -mthumb -gdwarf-2
INCS= -I .
SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o)

all: Pressure_Controller.hex
	@echo "=====DONE====="

%.o: %.c
	$(CC)gcc.exe -c $(CFLAGS) $(INCS) $< -o $@

Pressure_Controller.elf: $(OBJ)
	$(CC)ld.exe -T linker_script.ld $(OBJ) -o $@ -Map=Map_file.map

Pressure_Controller.hex: Pressure_Controller.elf
	$(CC)objcopy.exe -O binary $< $@

clean: 
	rm *.o *.hex *.elf 
	@echo "=====Clean_ALL====="
