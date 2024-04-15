
CUR_DIR := .

all:
	gcc -o learnfile learnfile.c
	$(CUR_DIR)/learnfile
clean:
	rm -rf learnfile
	rm -rf text.txt