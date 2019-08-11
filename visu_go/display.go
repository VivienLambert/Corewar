package main

import (
	"fmt"
	"os"
	"strconv"
	"strings"
	"time"

	"github.com/veandco/go-sdl2/sdl"
	"github.com/veandco/go-sdl2/ttf"
)

func tick(chDur chan time.Duration, chTick chan bool) {
	var dur time.Duration
	for {
		select {
		case dur = <-chDur:
		default:
			if dur != 0.0 {
				chTick <- true
				time.Sleep(dur)
			}
		}
	}
}

func printInfos(stdin string, surface *sdl.Surface, font *ttf.Font, window *sdl.Window, color [5]sdl.Color, w, h int32) {
	var solid *sdl.Surface
	var err error
	var i int

	i = 0

	if len(stdin) == 0 {
		return
	}

	line := sdl.Rect{
		X: 2060 * w / 2560,
		Y: 60 * h / 1440,
		W: 500 * w / 2560,
		H: 20 * h / 1440,
	}

	background := sdl.Rect{
		X: 2050 * w / 2560,
		Y: 50 * h / 1440,
		W: 500 * w / 2560,
		H: 1350 * h / 1440,
	}

	stdin = stdin[:len(stdin)-1]
	lines := strings.Split(stdin, "\n")
	surface.FillRect(&background, 0xff000000)
	for key := range lines {
		if len(lines[key]) != 0 {
			if strings.Contains(lines[key], "---PLAYER[") && i < 4 {
				i++
			}
			if solid, err = font.RenderUTF8Solid(lines[key], color[i]); err != nil {
				fmt.Fprintf(os.Stderr, "Failed to render text: %s\n", err)
				panic(err)
			}
			defer solid.Free()
			if err = solid.Blit(nil, surface, &line); err != nil {
				fmt.Fprintf(os.Stderr, "Failed to put text on window surface: %s\n", err)
				panic(err)
			}
		}
		line.Y += 35 * h / 1440
	}
}

func printArena(stdin string, surface *sdl.Surface, font *ttf.Font, window *sdl.Window, color [5]sdl.Color, backColor [5]uint32, w, h int32) {
	var solid *sdl.Surface
	var err error
	var i int
	var j int

	i = 0
	j = 0

	if len(stdin) == 0 {
		return
	}
	arena := sdl.Rect{
		X: 60 * w / 2560,
		Y: 60 * h / 1440,
		W: 28 * w / 2560,
		H: 25 * h / 1440,
	}
	background := sdl.Rect{
		X: 50 * w / 2560,
		Y: 50 * h / 1440,
		W: 1950 * w / 2560,
		H: 1350 * h / 1440,
	}
	surface.FillRect(&background, 0xff000000)
	for key := 0; key+2 < len(stdin); key += 2 {
		switch stdin[key] {
		case 'R':
			j = 1
		case 'Y':
			j = 4
		case 'P':
			j = 3
		case 'G':
			j = 2
		default:
			j = 0
		}
		switch stdin[key+1] {
		case 'R':
			i = 1
		case 'Y':
			i = 4
		case 'P':
			i = 3
		case 'G':
			i = 2
		default:
			i = 0
		}
		key += 2
		if j != 0 {
			surface.FillRect(&arena, backColor[j])
		}
		if key+2 <= len(stdin) && key%2 == 0 {
			if solid, err = font.RenderUTF8Solid(stdin[key:key+2], color[i]); err != nil {
				fmt.Fprintf(os.Stderr, "Failed to render text: %s\n", err)
				panic(err)
			}
			defer solid.Free()
			if err = solid.Blit(nil, surface, &arena); err != nil {
				fmt.Fprintf(os.Stderr, "Failed to put text on window surface: %s\n", err)
				panic(err)
			}
			arena.X += 30 * w / 2560
			if arena.X+arena.W > background.X+background.W {
				arena.X = 60 * w / 2560
				arena.Y += 20 * h / 1440
			}
		}
	}
}

func gradientBackground(infos string, w int32, loadingColor *uint32, surface *sdl.Surface, loading sdl.Rect) {
	split := strings.Split(infos, "\n")
	if len(split) >= 3 {
		cycles := strings.Split(split[2], " ")
		if len(cycles) == 5 {
			if cycle, err := strconv.Atoi(cycles[2]); err == nil {
				if cycleToDie, err := strconv.Atoi(cycles[4]); err == nil {
					loading.W = w * int32(cycle) / int32(cycleToDie)
					if loading.W != 0 {
						if (cycleToDie >= 510 && cycle%(cycleToDie/510) == 0 &&
							*loadingColor+uint32(0x00010000*(1+510/cycleToDie)) <= 0x00ff0000) ||
							(cycleToDie < 510 && *loadingColor+uint32(0x00010000*(1+510/cycleToDie)) <= 0x00ff0000) {
							*loadingColor += uint32(0x00010000 * (1 + 510/cycleToDie))
						} else if (cycleToDie >= 510 && cycle%(cycleToDie/510) == 0 && *loadingColor-uint32(0x00000100*(1+510/cycleToDie)) >= 0x00ff0000) ||
							(cycleToDie < 510 && *loadingColor-uint32(0x00000100*(1+510/cycleToDie)) >= 0x00ff0000) {
							*loadingColor -= uint32(0x00000100 * (1 + 510/cycleToDie))
						} else if (cycleToDie >= 510 && cycle%(cycleToDie/510) == 0) || cycleToDie < 510 {
							*loadingColor |= 0x00ff0000
						}
						if cycle == 1 {
							*loadingColor = 0x0000ff00
						}
						surface.FillRect(&loading, *loadingColor)
					}
				}
			}
		}
	}
}

func update(chMem, chInfos chan string, fontMem, fontInfos *ttf.Font, tick chan bool,
	surface *sdl.Surface, window *sdl.Window, color [5]sdl.Color, backColor [5]uint32, w, h int32, loadingColor *uint32) {
	var infos, mem string

	loading := sdl.Rect{
		X: 0,
		Y: 0,
		W: 0,
		H: h,
	}

	select {
	case <-tick:
		select {
		case mem = <-chMem:
			infos = <-chInfos
			if len(infos) > 1 {
				surface.FillRect(nil, 0xff404040)
				gradientBackground(infos, w, loadingColor, surface, loading)
				printArena(mem, surface, fontMem, window, color, backColor, w, h)
				printInfos(infos, surface, fontInfos, window, color, w, h)
				window.UpdateSurface()
			}
		default:
			return
		}
	default:
		return
	}
}