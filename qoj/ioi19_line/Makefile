INPUT_DIR 	:= data/tests
OUTPUT_DIR	:= output

INPUTS  := $(wildcard $(INPUT_DIR)/*.in)
OUTPUTS := $(patsubst $(INPUT_DIR)/%.in, $(OUTPUT_DIR)/%.out, $(INPUTS))

FLAGS	:= -std=c++23 -g -Og -fsanitize=address,undefined -DLOCAL -DDEBUG
TARGET	:= ./sol
SOURCES	:= solution.cpp

all: $(TARGET) $(OUTPUTS)

zip: $(OUTPUTS)
	mkdir zip
	for i in $$(seq -w 1 10); do \
		cp $(OUTPUT_DIR)/$$i.out zip/$$(expr $$i + 0).ans; \
	done
	(cd zip && zip ../submission.zip *.ans)
	rm -rf zip

$(TARGET): $(SOURCES)
	g++ $(FLAGS) -o $@ $<

$(OUTPUT_DIR)/%.out: $(INPUT_DIR)/%.in $(TARGET)
	@mkdir -p $(OUTPUT_DIR)
	@echo "============= Test $* ============="
	$(TARGET) < $< > $@
	@echo "Score: $$(head -n 1 $@)"

clean:
	rm $(TARGET)
	rm -r $(OUTPUT_DIR)

.PHONY: all zip clean
