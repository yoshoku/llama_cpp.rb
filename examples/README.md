# llama_cpp.rb/examples

## chat.rb

### Usage

```sh
$ cd examples
$ gem install llama_cpp thor
$ ./chat.rb -m /path/to/quantized-model.bin -t 4
...
User: Please tell me the largest city in Japan.
Bob: Sure. The largest city in Japan is Tokyo.
User:
```

### Options

```sh
$ ./chat.rb help main
Usage:
  chat.rb main -m, --model=MODEL

Options:
  -s, [--seed=N]                         # random seed
                                         # Default: -1
  -t, [--threads=N]                      # number of threads
                                         # Default: 2
  -m, --model=MODEL                      # path to model file
  -f, [--file=FILE]                      # prompt file to start generation
  -r, [--reverse-prompt=REVERSE_PROMPT]  # halt generation at PROMPT, return control in interactive mode
  -b, [--batch-size=N]                   # batch size for prompt processing
                                         # Default: 1024
  -n, [--n-predict=N]                    # number of tokens to predict
                                         # Default: 256
      [--keep=N]                         # number of tokens to keep from the initial prompt
                                         # Default: 48
      [--repeat-last-n=N]                # last n tokens to consider for penalize
                                         # Default: 64
      [--repeat-penalty=N]               # penalize repeat sequence of tokens
                                         # Default: 1.0
      [--presence-penalty=N]             # repeat alpha presence penalty
                                         # Default: 0.0
      [--frequency-penalty=N]            # repeat alpha frequency penalty
                                         # Default: 0.0
      [--top-k=N]                        # top k sampling
                                         # Default: 40
      [--top-p=N]                        # top p sampling
                                         # Default: 0.95
      [--tfs-z=N]                        # tail free sampling, parameter z
                                         # Default: 1.0
      [--typical-p=N]                    # locally typical sampling, parameter p
                                         # Default: 1.0
      [--temp=N]                         # temperature
                                         # Default: 0.8
      [--n-gpu-layers=N]                 # number of layers on GPU
                                         # Default: 0

Start chat
```

## embedding.rb

### Usage

```sh
$ cd examples
$ gem install llama_cpp thor
$ ./embedding.rb -m /path/to/quantized-model.bin -t 4 -p 'Hello, World.'
...
0.7191136479377747 0.5564611554145813 1.4210394620895386 -1.4874695539474487
```

### Options

```
$ ./embedding.rb help main
Usage:
  embedding.rb main -m, --model=MODEL -p, --prompt=PROMPT

Options:
  -s, [--seed=N]          # random seed
                          # Default: -1
  -t, [--threads=N]       # number of threads
                          # Default: 2
  -m, --model=MODEL       # path to model file
  -p, --prompt=PROMPT     # prompt to generate embedding
      [--n-gpu-layers=N]  # number of layers on GPU
                          # Default: 0

Extract embedding from prompt
```
