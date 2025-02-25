# cli-organizer
Lightweight command-line tool for organizing files and folders, written in C++

## Running
To compile for your machine, downlaod the file and run ```g++ <filepath> -o organize``` (or clang, depending on the compiler you're using). All the included headers should be cross-platform, however it does use the 'algorithm' lib, which requires a c++17 compiler. Make sure to keep ```settings.txt``` in the same directory as the executable. 

After that, you can run the command as easily as this:

```organize <filepath> --sf (optional) --force (optional)```

organize - command name

<filepath> - folder that you want to organize (e.g. C:/Users/bush/Downloads)

--sf - Whether or not you want to sort the folders into a ```Folders``` folder. This will NOT sort the already organized folders, however if you change around the key values in ```settings.txt``` and run on an already organized folder then it'll probably organize the folders, so I'll probably add a ```disorganize``` script later to avoid this.

--force - Whether you want confirmation for the sort or not. If you don't put the flag, it'll prompt you asking, "You want to sort this folder: ```folder``` , correct?" If you do put the flag, no confirmation will be asked and it'll just run the script. 

## Modifying the sorting
In ```settings.txt```, you can simply change any pair that you want, add new pairs, or even remove them. For example, you can add ```Songs: mp3``` if you want to sort .mp3 files as well. Keep in mind that you do NOT put the ```.``` before the extension, the script is built to not have these. Don't put any commas or anything like that, just spaces between each arg (```Songs: mp3 song mp2```).

## Unsupported formats
Due to UTF restrictions and type conversions between str and char (for renaming files), certain files may not sort properly (This is normally because of weird characters, however sometimes the script doesn't have access to move the folder). The tool has built-in features which tell you what files/folders it's unable to sort, like this:

Unable to sort file: ! ┬º9VENOM ┬º8┬ºl[┬ºf┬º816x┬ºl] ┬ºf┬º8REVAMP.zip

Unable to sort file: Kami Export - Copy of AP Calculus BC_ Day 5 ΓÇô 8 Review (1).pdf

Unable to sort file: Kami Export - Copy of AP Calculus BC_ Day 5 ΓÇô 8 Review (2).pdf

Unable to sort file: Kami Export - Copy of AP Calculus BC_ Day 5 ΓÇô 8 Review (3).pdf

Unable to sort file: Kami Export - Copy of AP Calculus BC_ Day 5 ΓÇô 8 Review (4).pdf

Unable to sort file: Kami Export - Copy of AP Calculus BC_ Day 5 ΓÇô 8 Review.pdf

Unable to sort folder: Starter Packet

That way, you can easily go in your file explorer app and move them by hand, if you desire. MAKE SURE TO DO THIS IF YOU MIGHT DISORGANIZE LATER OTHERWISE IT WILL UNPACK ALL FOLDERS WHICH COULD BE BAD.
