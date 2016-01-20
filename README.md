# Life

This is, really, my idea of how one would go about creating "life" on a computer. This program does one thing: It produces slightly modified versions of itself and starts them. They could be better, they could be worse, they could issue `F00F C7C8`. It's all undefined. Basically a forkbomb.

## Building

Simply run:

```
make
```

## Running

**DO NOT RUN ON HARDWARE YOU CARE ABOUT.** This is why I have a Raspberry Pi. Before you ruin your computer, just go and pick up a Pi.

Once you've run `make`, you'll have an executable called `life`. Run it.

```
./life
```

I recommend using Tmux with this program running in one pane and `top` in the other. That way, you can watch resource consumption (which is really the best way to observe the "lifeforms").

## Contributing

If you think this blasphemy is wonderful and want to contribute, you can. That said, it is supposed to remain as small and simple as possible, so please try to avoid adding features.

Steps to contribute:
1. Fork this repository
2. Create a branch on your fork for your work
3. Do your work on that branch
4. Push it to GitHub
5. Send me a pull-request
6. Profit?
