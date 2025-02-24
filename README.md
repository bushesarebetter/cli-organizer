# cli-organizer
Lightweight command-line tool for organizing files and folders, written in C++

## Running
To compile for your machine, downlaod the file and run ```g++ <filepath> -o organize``` (or clang, depending on the compiler you're using). Make sure to keep ```settings.txt``` in the same directory as the executable. 

After that, you can run the command as easily as this:

```organize <filepath> --sf (optional)```

organize - command name

<filepath> - folder that you want to organize (e.g. C:/Users/bush/Downloads)

--sf - Whether or not you want to sort the folders into a ```Folders``` folder. This will NOT sort the already organized folders, however if you change around the key values in ```settings.txt``` and run on an already organized folder then it'll probably organize the folders, so I'll probably add a ```disorganize``` script later to avoid this.

## Modifying the sorting
In ```settings.txt```, you can simply change any pair that you want, add new pairs, or even remove them. For example, you can add ```Songs: mp3``` if you want to sort .mp3 files as well. Keep in mind that you do NOT put the ```.``` before the extension, the script is built to not have these. Don't put any commas or anything like that, just spaces between each arg (```Songs: mp3 song mp2```).
