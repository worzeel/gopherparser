OUT=gopherparser

$(OUT): $(OUT).c
	@echo building... $(OUT)
	@cc -o $(OUT) $(OUT).c

clean:
	@echo cleaning...
	@rm -f $(OUT)