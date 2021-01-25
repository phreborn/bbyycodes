g++ -I. `root-config --libs --cflags` -lRooFitCore -lRooFit -lRooStats -lTMVA -lXMLIO -lTreePlayer -o $1 $1.C
