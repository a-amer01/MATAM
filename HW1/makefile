CC = gcc
OBJS = matamikya.o matamikya_orders.o matamikya_print.o matamikya_product.o matamikya_main.o matamikya_tests.o
EXEC = matamikya
EXECSTR = amount_set_str
OBJSSTR = amount_set_str.o amount_set_str_main.o amount_set_str_tests.o
LIBS = libas.a libmtm.a
COMPILE_FLAGS = -std=c99 -Wall -pedantic-errors -Werror -DNDEBUG
DEBUG_FLAGS =  -DNDEBUG -g

$(EXEC): $(OBJS)
	$(CC) $(DEBUG_FLAGS) $(LIBS) $(OBJS) -o $@ -L. -lmtm -lm -las

matamikya.o: matamikya.c matamikya.h matamikya_print.h set.h amount_set.h matamikya_product.h matamikya_orders.h
	$(CC) -c $(DEBUG_FLAGS) $(COMPILE_FLAGS)  $*.c

matamikya_orders.o: matamikya_orders.c matamikya_orders.h matamikya.h set.h amount_set.h matamikya_product.h
	$(CC) -c $(DEBUG_FLAGS) $(COMPILE_FLAGS) $*.c

matamikya_print.o:matamikya_print.c matamikya_print.h
	$(CC) -c $(DEBUG_FLAGS) $(COMPILE_FLAGS) $*.c

matamikya_product.o: matamikya_product.c matamikya_product.h matamikya.h amount_set.h
	$(CC) -c $(DEBUG_FLAGS) $(COMPILE_FLAGS) $*.c
	
matamikya_main.o: ./tests/matamikya_tests.h ./tests/matamikya_main.c  ./tests/test_utilities.h  
	$(CC) -c $(DEBUG_FLAGS) $(COMPILE_FLAGS) $/tests/*.c
	
matamikya_tests.o: tests/matamikya_tests.c tests/matamikya_tests.h matamikya.h tests/test_utilities.h
	$(CC) -c $(DEBUG_FLAGS) $(COMPILE_FLAGS) $*.c

$(EXECSTR): $(OBJSSTR)
	$(CC) $(DEBUG_FLAGS)  $(OBJSSTR) -o $@

amount_set_str.o: amount_set_str.c amount_set_str.h
	$(CC) -c $(DEBUG_FLAGS) $(COMPILE_FLAGS) $*.c

amount_set_str_main.o: amount_set_str_main.c amount_set_str.h test_utilities.h amount_set_str_tests.h
	$(CC) -c $(DEBUG_FLAGS) $(COMPILE_FLAGS) $*.c

amount_set_str_tests.o: amount_set_str_tests.c test_utilities.h amount_set_str.h
	$(CC) -c $(DEBUG_FLAGS) $(COMPILE_FLAGS) $*.c

clean:
	rm -f $(OBJS) $(EXEC)
	rm -f $(OBJSSTR) $(EXECSTR)
	
	
