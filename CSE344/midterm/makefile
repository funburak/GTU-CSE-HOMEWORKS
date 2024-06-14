SERVER_DIR = server
CLIENT_DIR = client

all: clear clean compile

clear:
	@clear

clean:
	@rm -f $(SERVER_DIR)/neHosServer
	@rm -f $(CLIENT_DIR)/neHosClient

compile:
	@gcc -pthread -o  $(SERVER_DIR)/neHosServer $(SERVER_DIR)/server.c
	@gcc -pthread -o $(CLIENT_DIR)/neHosClient $(CLIENT_DIR)/client.c