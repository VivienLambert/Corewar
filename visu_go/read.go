package main

import (
	"bufio"
)

func testPipe(in *bufio.Reader) bool {
	if test, err := in.ReadByte(); err != nil || test != 'O' {
		return false
	}
	if test, err := in.ReadByte(); err != nil || test != 'K' {
		return false
	}
	return true
}

func scan(in *bufio.Reader, chMem, chInfos chan string) {
	var stdin string
	var err error

	for {
		stdin, err = in.ReadString(';')
		if err != nil {
			close(chMem)
			close(chInfos)
			return
		}
		chMem <- stdin
		stdin, err = in.ReadString(';')
		if err != nil {
			close(chMem)
			close(chInfos)
			return
		}
		chInfos <- stdin
	}
}