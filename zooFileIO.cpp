#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>

class Animal {
public:
    Animal(const std::string& name, int age, const std::string& species)
        : name(name), age(age), species(species) {}
    std::string getName() const { return name; }
    int getAge() const { return age; }
    std::string getSpecies() const { return species; }

private:
    std::string name;
    int age;
    std::string species;
};

class Hyena : public Animal {
public:
    Hyena(const std::string& name, int age) : Animal(name, age, "Hyena") {}
};

class Lion : public Animal {
public:
    Lion(const std::string& name, int age) : Animal(name, age, "Lion") {}
};

class Tiger : public Animal {
public:
    Tiger(const std::string& name, int age) : Animal(name, age, "Tiger") {}
};

class Bear : public Animal {
public:
    Bear(const std::string& name, int age) : Animal(name, age, "Bear") {}
};

std::vector<Animal> readAnimalsFromFile(const std::string& filePath) {
    std::vector<Animal> animals;
    std::ifstream inputFile(filePath);
    if (!inputFile.is_open()) {
        std::cerr << "Error opening file: " << filePath << std::endl;
        return animals;
    }

    std::string line;
    while (std::getline(inputFile, line)) {
        std::string name, species;
        int age;
        std::istringstream iss(line);
        if (iss >> name >> age >> species) {
            if (species == "Hyena")
                animals.push_back(Hyena(name, age));
            else if (species == "Lion")
                animals.push_back(Lion(name, age));
            else if (species == "Tiger")
                animals.push_back(Tiger(name, age));
            else if (species == "Bear")
                animals.push_back(Bear(name, age));
        }
    }

    inputFile.close();
    return animals;
}

void generateReport(const std::vector<Animal>& animals, const std::string& outputFile) {
    std::map<std::string, int> speciesCounts;
    for (const Animal& animal : animals) {
        speciesCounts[animal.getSpecies()]++;
    }

    std::ofstream outFile(outputFile);
    if (!outFile.is_open()) {
        std::cerr << "Error opening file: " << outputFile << std::endl;
        return;
    }

    for (const auto& entry : speciesCounts) {
        outFile << entry.first << ": " << entry.second << std::endl;
    }

    outFile.close();
    std::cout << "Report generated and saved to " << outputFile << std::endl;
}

int main() {
    std::string inputFilePath = "arrivingAnimals.txt";
    std::string outputFilePath = "newAnimals.txt";

    std::vector<Animal> animals = readAnimalsFromFile(inputFilePath);
    generateReport(animals, outputFilePath);

    return 0;
}
