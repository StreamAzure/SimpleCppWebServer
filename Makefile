server:
	g++ util.cpp client.cpp -o client && \
	g++ util.cpp server.cpp -o server

.PHONY : clean
clean:
	rm server && rm client