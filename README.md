# REST API & CLI
A REST API and CLI program written in C

## 🗂 Table of Contents
* [Getting Started](#-getting-started)
* [REST API](#-rest-api)
* [CLI](#-cli)
* [Main External Libraries Used](#-main-external-libraries-used)

## 🏁 Getting Started
A Linux OS and the `gcc` compiler are needed.

#### ⚙️ Installing
To compile the code, clone the repo, and run the following commands.
```
$ git clone https://github.com/filipebafica/c_rest_api.git
$ cd c_rest_api
$ make
```
This is going to generate two executables named `server` and `cli`.

To run the server:
`./server`

To run the cli:
`./cli`

## 🌐 REST API
Currently the API provides the method `GET` in two paths:

1 - Root path: `/` which will return all books from the database
![image](https://user-images.githubusercontent.com/31427890/155892553-def2d349-4554-4d50-a96c-25d89d720be2.png)

2 - Book path `/book` which will return a specific book from the database. The query must follow the pattern `/book?id=[book_id]`
![image](https://user-images.githubusercontent.com/31427890/155892647-bb81e75c-becb-468d-af15-f50515dbb9a1.png)

## 💻 CLI
The cli program will return the number of requests made to the API since the last time the server was started:
![image](https://user-images.githubusercontent.com/31427890/155892700-84aea1f6-2300-4df4-b058-0b6ee1583195.png)

## 📚 Main External Libraries Used
* [cJSON - Ultralightweight JSON parser in ANSI C](https://github.com/DaveGamble/cJSON)
* [mongoose - Embedded Web Server](https://mongoose.ws/)
* [SQLite](https://www.sqlite.org/index.html)
* [libft - libc implementations from scratch](https://github.com/filipebafica/libft)
