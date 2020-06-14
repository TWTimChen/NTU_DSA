source = hw6_2_1 hw6_2_2 hw6_2_3
all: $(source)
$(source):
%: %.c avl bst rb
	gcc avl.o bst.o rb.o $< -o $@

avl: avl.c avl.h
	gcc avl.c -c

bst: bst.c bst.h
	gcc bst.c -c

rb: rb.c rb.h
	gcc rb.c -c

clean:
	rm -rf $(source) *.o