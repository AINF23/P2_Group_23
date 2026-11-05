# COP3530 - Project 2
## TV Show Search Engine

This project is a search engine for TV shows that lets you filter and sort by genre, rating, release year, number of seasons and episodes, or even look up by name.

Created by: Nyden Rodewald, Isabella Vassor, and Andres Noguera

### Features

- Filter by title, genre, minimum rating, year range, seasons, and episodes.
- Sort with quick sort, merge sort, and heap sort.
- Shows how long each search and sort takes for comparison.
- Web page using a local server.

### Data

This project uses the IMDb non-commercial datasets. The data files must be downloaded since they are too large for GitHub.
These are the steps:

1. Download these files from https://datasets.imdbws.com/:
	- "title.basics.tsv.gz"
	- "title.ratings.tsv.gz"
	- "title.episode.tsv.gz"
2. Unzip them.
3. Create a folder named "data" in the project root and put the three .tsv files inside.

TV shows will be loaded from the year 1950 or later and with at least 100 rating votes on IMDb.

### Building and running

Use CLion/VS Code or any Cmake setup with a C++17 compiler.

1. Clone the repo and add the "data/" folder.
2. Open the project and load CMakeLists.txt.
3. Select the "sever" run configuration and run.
4. Wait for the confirmation "open browser test", this may take up to a minute.
5. Open "http://localhost:8080" in any browser.

### How it works

1. The loader reads the three IMDb files and builds a vector of TVShow objects.
2. The Database filters the list based on a Query or filters.
3. The results are sorted and sent to the web page as JSON.

### Credits
- IMDb datasets
-  httplib.h  Copyright (c) 2026 Yuji Hirose
