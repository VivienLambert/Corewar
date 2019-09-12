package main

import (
	"time"

	"github.com/veandco/go-sdl2/sdl"
)

func handleKeys(chDur chan time.Duration, dur *time.Duration, stop *bool) bool {
	event := sdl.PollEvent()
	if event != nil {
		switch test := event.(type) {
		case *sdl.QuitEvent:
			println("Quit")
			return false
		case *sdl.KeyboardEvent:
			if test.State == sdl.PRESSED && test.Keysym.Sym == sdl.K_ESCAPE {
				println("Quit")
				return false
			} else if test.State == sdl.PRESSED && test.Keysym.Sym == sdl.K_EQUALS {
				if (*dur) > 1000000.0 {
					*dur /= 2.0
					chDur <- *dur
				} else {
					*dur = 1000000.0
					if *stop == true {
						chDur <- *dur
					}
				}
				*stop = false
			} else if test.State == sdl.PRESSED && test.Keysym.Sym == sdl.K_MINUS {
				if (*dur).Seconds() < 1 {
					*dur *= 2
					if *stop == false {
						chDur <- *dur
					}
				} else {
					*dur = time.Second
				}
			} else if test.State == sdl.PRESSED && test.Keysym.Sym == sdl.K_SPACE {
				if *stop == false {
					*stop = true
					chDur <- 0
				} else {
					*stop = false
					chDur <- *dur
				}
			}
		}
	}
	return true
}
