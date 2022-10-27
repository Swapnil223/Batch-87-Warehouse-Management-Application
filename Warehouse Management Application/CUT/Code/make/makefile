warehouse:main_menu.o admin_file_maintenance.o validation_data.o
	gcc -o ../bin/warehouse ../obj/main_menu.o ../obj/admin_file_maintenance.o ../obj/validation_data.o

main_menu.o: ../SRC/main_menu.c
	gcc -c ../SRC/main_menu.c -o ../obj/main_menu.o

admin_file_maintenance.o: ../SRC/admin_file_maintenance.c
	gcc -c ../SRC/admin_file_maintenance.c -o ../obj/admin_file_maintenance.o

validation_data.o: ../SRC/validation_data.c
	gcc -c ../SRC/validation_data.c -o ../obj/validation_data.o

clean:
	rm *.o
