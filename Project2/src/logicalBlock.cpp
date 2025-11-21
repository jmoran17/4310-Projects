#include <iostream>
using namespace std;

int main() {
    int LBN, cylinders, tracks, sectors;

    cout << "Enter logical block number: ";
    cin >> LBN;
    cout << "Enter HD number of cylinders: ";
    cin >> cylinders;
    cout << "Enter HD number of tracks: ";
    cin >> tracks;
    cout << "Enter HD number of sectors: ";
    cin >> sectors;

    int sectorsPerCylinder = tracks * sectors;

    int cylinderNum = LBN / sectorsPerCylinder;
    int remainder = LBN % sectorsPerCylinder;
    int trackNum = remainder / sectors;
    int sectorNum = remainder % sectors;

    cout << "The logical block number " << LBN
         << " is located at <" << cylinderNum
         << ", " << trackNum << ", " << sectorNum << ">" << endl;
    return 0;
}
