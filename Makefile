SUBDIRS := $(addsuffix .subdir,$(sort $(basename $(dir $(wildcard */Makefile)))))


all: $(SUBDIRS)
	@echo "Finished building $@"

%.subdir:
	$(MAKE) -C $(basename $@)

.PHONY: clean
clean:
	for dir in $(dir $(wildcard */Makefile)); do $(MAKE) -C $${dir} clean; done
