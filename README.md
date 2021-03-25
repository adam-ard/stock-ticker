# Stock Ticker

A simple stock reporter, based on the free api at https://polygon.io/.
It is a QT application with a list of stocks. Simple information and logo
are displayed in the list, and details are loaded based on which stock is
selected.

## Installation (Ubuntu)

Install qt5

```bash
sudo apt-get install qt5-default
```

## To build the application

To build this application run the following:

```bash
qmake
make
```

## To Run

Pass an Api key as an environment variable, and invoke
stock_ticker directly

```bash
POLYGON_API_KEY=xxxxxxxxxxxxxxxx ./stock-ticker
```

## To Build Tests

To build the test application run the following:

```bash
qmake "CONFIG += test"
make
```

## To Run Tests

```bash
./tests
```
