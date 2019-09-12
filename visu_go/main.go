package main

import (
	"bufio"
	"fmt"
	"os"
	"time"

	"github.com/veandco/go-sdl2/sdl"
	"github.com/veandco/go-sdl2/ttf"
)

func main() {
	var window *sdl.Window
	var surface *sdl.Surface
	var err error
	var dur time.Duration
	var fontMem, fontInfos *ttf.Font
	var stop bool
	var color [5]sdl.Color
	var backColor [5]uint32
	var loadingColor uint32

	in := bufio.NewReader(os.Stdin)

	if testPipe(in) == false {
		fmt.Fprintf(os.Stderr,
			"\nHello it's visu...\nDo you even use your brain?\nGive me only corewar with -V and correct champions and options!!!\nAnyway, have a nice day...\n")
		return
	}

	if err = sdl.Init(sdl.INIT_EVERYTHING); err != nil {
		panic(err)
	}
	defer sdl.Quit()

	if err = ttf.Init(); err != nil {
		fmt.Fprintf(os.Stderr, "Failed to initialize TTF: %s\n", err)
		panic(err)
	}
	defer ttf.Quit()

	window, err = sdl.CreateWindow("", sdl.WINDOWPOS_UNDEFINED, sdl.WINDOWPOS_UNDEFINED,
		0, 0, sdl.WINDOW_FULLSCREEN_DESKTOP)
	if err != nil {
		panic(err)
	}
	defer window.Destroy()

	w, h := window.GetSize()

	if fontMem, err = ttf.OpenFont("visu_go/ArcadeClassic.ttf", 25*int(h)/1440); err != nil {
		fmt.Fprintf(os.Stderr, "Failed to open font: %s\n", err)
		panic(err)
	}
	defer fontMem.Close()

	if fontInfos, err = ttf.OpenFont("visu_go/Rubik-Regular.ttf", 25*int(h)/1440); err != nil {
		fmt.Fprintf(os.Stderr, "Failed to open font: %s\n", err)
		panic(err)
	}
	defer fontInfos.Close()

	surface, err = window.GetSurface()
	if err != nil {
		panic(err)
	}
	defer surface.Free()

	chMem := make(chan string, 20000)
	chInfos := make(chan string, 20000)
	chDur := make(chan time.Duration, 1)
	chTick := make(chan bool, 100)

	color[0] = sdl.Color{R: 255, G: 255, B: 255, A: 255}
	color[1] = sdl.Color{R: 255, G: 0, B: 0, A: 255}
	color[2] = sdl.Color{R: 0, G: 255, B: 0, A: 255}
	color[3] = sdl.Color{R: 128, G: 0, B: 255, A: 255}
	color[4] = sdl.Color{R: 255, G: 255, B: 0, A: 255}

	backColor[1] = 0xffaa0000
	backColor[2] = 0xff00aa00
	backColor[3] = 0xff5500aa
	backColor[4] = 0xffaaaa00

	loadingColor = 0x0000ff00

	stop = true
	dur = 1 * time.Second
	chDur <- 0
	chTick <- true

	go scan(in, chMem, chInfos)
	go tick(chDur, chTick)

	for {
		if handleKeys(chDur, &dur, &stop) == false {
			return
		}
		update(chMem, chInfos, fontMem, fontInfos, chTick, surface, window, color, backColor, w, h, &loadingColor)
	}
}
