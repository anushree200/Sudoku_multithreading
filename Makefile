final:
	@echo "Build Version 1.0.1"
	@sleep 3
	@echo "Entering Sudoku Validation using Multithreading Assignment"
	@sleep 4
	@echo "Compiling The Sequential first"
	gcc Assign1src3-CO23BTECH11003.c -o out -lm
	@echo "Completing the compilation..."
	@sleep 3
	@./out
	@sleep 3
	@echo "Compiling the Chunk file next."
	@sleep 3
	gcc Assign1src1-CO23BTECH11003.c -o out -lm
	@echo "Completing the compilation..."
	@sleep 3
	@./out
	@sleep 3
	@echo "Compiling the Mixed file next."
	@sleep 3
	gcc Assign1src2-CO23BTECH11003.c -o out -lm
	@echo "Completing the compilation..."
	@sleep 3
	@./out
	@sleep 3
	@echo "Created outputseq.txt with output of sequential validation, outputchunk.txt for chunk method and outputmixed.txt for mixed method"
	@echo "Makefile Success!!"