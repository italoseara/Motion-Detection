# Motion Detection

This project is a simple motion detection algorithm that uses Image Subtraction to see if there was any movement between two consecutive frames. The algorithm is implemented using C++ and makes use of .ppm images to store the frames.

## Compiling

To run the project, you need to have a C++ compiler installed on your machine. I used the GNU Compiler Collection (g++) to compile the code. To compile the code, you can use the following command:

```bash
make build
```

## Running

To run the project, you can use the following command:

```bash
make run ARGS="path/to/first/image.ppm path/to/second/image.ppm <threshold>"
```

or

```bash
./build/main path/to/first/image.ppm path/to/second/image.ppm <threshold>
```

where `<threshold>` is the value that will be used to determine if a pixel has changed or not.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Authors

- [Italo Seara](https://github.com/italoseara)
