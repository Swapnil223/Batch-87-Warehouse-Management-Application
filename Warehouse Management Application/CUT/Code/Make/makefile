warehouse:main_menu.o admin_file_maintenance.o validation_data.o
	gcc -o warehouse main_menu.o admin_file_maintenance.o validation_data.o

main_menu.o:main_menu.c header.h 
	gcc -c main_menu.c 

admin_file_maintenance.o:admin_file_maintenance.c header.h
	gcc -c admin_file_maintenance.c

validation_data.o:validation_data.c header.h
	gcc -c validation_data.c

clean:
	rm *.o
