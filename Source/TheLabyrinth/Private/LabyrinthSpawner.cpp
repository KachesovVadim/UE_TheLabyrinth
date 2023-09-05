// Fill out your copyright notice in the Description page of Project Settings.


#include "LabyrinthSpawner.h"

// LABYRINTH GENERATOR
#include <vector>
#include <random>
#include <map>

class Cell {
public:
    int x, y, rows, cols;
    bool visited;
    std::map<string, bool> walls;

    Cell(int x, int y, int rows, int cols) {
        this->x = x;
        this->y = y;
        this->rows = rows;
        this->cols = cols;
        this->visited = false;
        this->walls = { {"top", true}, {"right", true}, {"bottom", true}, {"left", true} };
    }

    Cell* check_cell(int xcoor, int ycoor, vector<Cell*>& grid_cells) {
        int index = xcoor + ycoor * cols;
        if (xcoor < 0 || xcoor > cols - 1 || ycoor < 0 || ycoor > rows - 1) {
            return nullptr;
        }
        return grid_cells[index];
    }

    Cell* check_neighbors(vector<Cell*>& grid_cells) {
        vector<Cell*> neighbors;
        Cell* top = check_cell(x, y - 1, grid_cells);
        Cell* right = check_cell(x + 1, y, grid_cells);
        Cell* bottom = check_cell(x, y + 1, grid_cells);
        Cell* left = check_cell(x - 1, y, grid_cells);
        if (top && !top->visited) {
            neighbors.push_back(top);
        }
        if (right && !right->visited) {
            neighbors.push_back(right);
        }
        if (bottom && !bottom->visited) {
            neighbors.push_back(bottom);
        }
        if (left && !left->visited) {
            neighbors.push_back(left);
        }
        if (!neighbors.empty()) {
            random_device rd;
            mt19937 gen(rd());
            uniform_int_distribution<> dis(0, neighbors.size() - 1);
            return neighbors[dis(gen)];
        }
        return nullptr;
    }
};

void remove_walls(Cell* current, Cell* next) {
    int dx = current->x - next->x;
    if (dx == 1) {
        current->walls["left"] = false;
        next->walls["right"] = false;
    }
    else if (dx == -1) {
        current->walls["right"] = false;
        next->walls["left"] = false;
    }
    int dy = current->y - next->y;
    if (dy == 1) {
        current->walls["top"] = false;
        next->walls["bottom"] = false;
    }
    else if (dy == -1) {
        current->walls["bottom"] = false;
        next->walls["top"] = false;
    }
}

void CheckExit(int rows, int cols, Cell* cell)
{
    if (cell->x == int(rows / 2) && cell->y == cols-1) // Sector enter
    {
        cell->walls["bottom"] = false;
        cell->walls["top"] = false;
        cell->walls["left"] = false;
        cell->walls["right"] = false;
    }
    else if (cell->x == int(rows / 2) && cell->y == 0) // Sector exit
    {
        cell->walls["top"] = false;
        cell->walls["left"] = false;
        cell->walls["right"] = false;
        cell->walls["bottom"] = false;
    }
}

vector<Cell*> GenerateMaze(int rows, int cols) 
{
    vector<Cell*> grid_cells;
    for (int y = 0; y < rows; y++) {
        for (int x = 0; x < cols; x++) {
            grid_cells.push_back(new Cell(x, y, rows, cols));
        }
    }

    Cell* current_cell = grid_cells[0];
    vector<Cell*> stack;

    while (true) {
        current_cell->visited = true;

        Cell* next_cell = current_cell->check_neighbors(grid_cells);
        if (next_cell) {
            next_cell->visited = true;
            stack.push_back(current_cell);
            remove_walls(current_cell, next_cell);
            current_cell = next_cell;
            CheckExit(rows, cols, current_cell);
        }
        else if (!stack.empty()) {
            current_cell = stack.back();
            stack.pop_back();
        }
        else {
            break;
        }
    }

    return grid_cells;
}

// Sets default values
ALabyrinthSpawner::ALabyrinthSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    static ConstructorHelpers::FObjectFinder<UStaticMesh> WallObj(TEXT("/Game/Meshes/Wall/Wall"));
    Wall = WallObj.Object;
}

// Called when the game starts or when spawned
void ALabyrinthSpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALabyrinthSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


//void ALabyrinthSpawner::SpawnStaticMeshActor(const FVector& InLocation, const FRotator& ActorRotation, vector<AStaticMeshActor*> &ASMA_walls, vector<UStaticMeshComponent*> &USMC_walls)
//{
//    ASMA_walls.push_back(GetWorld()->SpawnActor<AStaticMeshActor>(AStaticMeshActor::StaticClass(), InLocation, ActorRotation));
//    ASMA_walls.back()->SetMobility(EComponentMobility::Stationary);
//
//    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, ASMA_walls.back()->GetActorLocation().ToString());
//    USMC_walls.push_back(ASMA_walls.back()->GetStaticMeshComponent());
//    if (USMC_walls.back())
//    {
//        USMC_walls.back()->SetStaticMesh(Wall);
//        //GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, USMC_walls.back()->GetComponentLocation().ToString());
//    }
//}

void ALabyrinthSpawner::SpawnStaticMeshActor(const FVector& InLocation, const FRotator& ActorRotation)
{
    AStaticMeshActor* MyNewActor = GetWorld()->SpawnActor<AStaticMeshActor>(AStaticMeshActor::StaticClass(), InLocation, ActorRotation);
    MyNewActor->SetMobility(EComponentMobility::Stationary);

    UStaticMeshComponent* MeshComponent = MyNewActor->GetStaticMeshComponent();
    if (MeshComponent)
    {
        MeshComponent->SetStaticMesh(Wall);
    }
}

void PrintMazeToLog(int rows, int cols, std::vector<Cell*> grid_cells)
{
    string mline = "";

    for (int y = 0; y < rows; y++) {
        mline = "";
        for (int x = 0; x < cols; x++) {
            Cell* cell = grid_cells[x + y * cols];
            mline += "+";
            if (cell->walls["top"]) {
                mline += "---";
            }
            else {
                mline += "   ";
            }
        }
        mline += "+";
        GLog->Log(mline.c_str());
        mline = "";
        for (int x = 0; x < cols; x++) {
            Cell* cell = grid_cells[x + y * cols];
            if (cell->walls["left"]) {
                mline += "|";
            }
            else {
                mline += " ";
            }
            mline += "   ";
        }
        Cell* last_cell = grid_cells[(cols - 1) + y * cols];
        if (last_cell->walls["right"]) {
            mline += "|";
            GLog->Log(mline.c_str());
            mline = "";
        }
        else {
            mline += " ";
            GLog->Log(mline.c_str());
            mline = "";
        }
    }
    for (int x = 0; x < cols; x++) {
        mline += "+---";
    }
    mline += "+";
    GLog->Log(mline.c_str());
    mline = "";
}

void ALabyrinthSpawner::SpawnWalls(int rows, int cols, FVector LocInWrld)
{
    vector<Cell*> grid_cells = GenerateMaze(rows, cols);
    FVector MazeLocation = LocInWrld;

    PrintMazeToLog(rows,cols,grid_cells);

    for (Cell* cell : grid_cells)
    {
        FVector CellLocation = FVector(cell->x*1000, cell->y*1000, 0.f) + MazeLocation;
        if (cell->walls["top"])
        {
            FVector ActorLocation = CellLocation - FVector(0.f, 500.f, 0.f);
            FRotator ActorRotation = FRotator(0.f, 90.f, 0.f);
            SpawnStaticMeshActor(ActorLocation, ActorRotation);
        }
        if (cell->walls["right"])
        {
            FVector ActorLocation = CellLocation - FVector(-500.f, 0.f, 0.f);
            FRotator ActorRotation = FRotator(0.f, 0.f, 0.f);
            SpawnStaticMeshActor(ActorLocation, ActorRotation);
        }
        if (cell->walls["bottom"])
        {
            FVector ActorLocation = CellLocation - FVector(0.f, -500.f, 0.f);
            FRotator ActorRotation = FRotator(0.f, 90.f, 0.f);
            SpawnStaticMeshActor(ActorLocation, ActorRotation);
        }
        if (cell->walls["left"])
        {
            FVector ActorLocation = CellLocation - FVector(500.f, 0.f, 0.f);
            FRotator ActorRotation = FRotator(0.f, 0.f, 0.f);
            SpawnStaticMeshActor(ActorLocation, ActorRotation);
        }
    }
}