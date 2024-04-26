//
// Created by Bryan on 13/04/2024.
//

#include <GameLoop.h>
#include <Paddle.h>
#include <SelectableText.h>
#include <Text.h>
#include <Brick.h>
#include <Ball.h>
#include <filesystem> // Pour accéder aux fonctionnalités de système de fichiers
#include <fstream>
#include <vector>

#define HEIGHT 800
#define WIDTH 640
#define PAD_W 100
#define PAD_H 20
#define PAD_SPEED 10


int menuSelection = 0;
// Couleurs de briques
std::vector<SDL_Color> brickColors = {
    {0, 0, 0, 0},
    {252, 169, 133, 255}, // Rouge
    {255, 237, 81, 255}, // Jaune
    {133, 202, 93, 255} // Vert
};

GameLoop::GameLoop() {
    window = nullptr;
    renderer = nullptr;
    defaultFont = nullptr;
    selectedFont = nullptr;
    defaultColor = {255, 255, 255, 255};  // Blanc
    selectedColor = {255, 0, 0, 255};  // Rouge
    WindowInit();
}

GameLoop::~GameLoop() {
    if (window != nullptr) {
        SDL_DestroyWindow(window);
    }
    if (renderer != nullptr) {
        SDL_DestroyRenderer(renderer);
    }
    if (defaultFont != nullptr) {
        TTF_CloseFont(defaultFont);
    }
    if (selectedFont != nullptr) {
        TTF_CloseFont(selectedFont);
    }
    SDL_Quit();
}

/*
 *  On initialise la fenêtre du jeu, le début de la partie, donc on init la balle, la raquette et les briques
 */
void GameLoop::WindowInit()
{
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        exit(1);
    }

    // Create a window
    window = SDL_CreateWindow("Brick Breaker", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        exit(1);
    }

    // Create a renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        exit(1);
    }

    // Clear the renderer
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Initialize SDL_ttf
    if (TTF_Init() == -1) {
        std::cerr << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError() << std::endl;
        exit(1);
    }
    // Initialize the fonts
    defaultFont = TTF_OpenFont("fonts/minecraft_font.ttf", 32);
    if (defaultFont == nullptr) {
        std::cerr << "Font could not be loaded! SDL_Error: " << SDL_GetError() << std::endl;
        exit(1);
    }
    selectedFont = TTF_OpenFont("fonts/minecraft_font.ttf", 36);
    if (defaultFont == nullptr) {
        std::cerr << "Font could not be loaded! SDL_Error: " << SDL_GetError() << std::endl;
        exit(1);
    }
}

void GameLoop::FirstPageLoop() {
    Text title(renderer, defaultColor, "Brick Breaker", defaultFont);
    SelectableText playTxt(renderer, defaultColor, selectedColor, "Play", defaultFont, selectedFont);
    SelectableText quitTxt(renderer, defaultColor, selectedColor, "Quit", defaultFont, selectedFont);
    // Rafraichissement de la page
    bool firstPage = true;
    bool gamePage = false;
    while (firstPage) {
        // Gestion des événements
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                firstPage = false;
            } else if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_LEFT:
                        std::cout << "Flèche gauche pressée" << std::endl;
                    break;
                    case SDLK_RIGHT:
                        std::cout << "Flèche droite pressée" << std::endl;
                    break;
                    case SDLK_UP:
                        std::cout << "Flèche haut pressée" << std::endl;
                        menuSelection = (menuSelection + 1) % 2;
                        SDL_RenderPresent(renderer);
                    break;
                    case SDLK_DOWN:
                        std::cout << "Flèche bas pressée" << std::endl;
                        menuSelection = (menuSelection + 1) % 2;
                        SDL_RenderPresent(renderer);
                    break;
                    case SDLK_ESCAPE:
                        std::cout << "Sortie du jeu." << std::endl;
                        firstPage = false;
                    break;
                    case SDLK_RETURN:
                        std::cout << "Selection du menu" << std::endl;
                        if (menuSelection == 0) {
                            firstPage = false;
                            gamePage = true;
                        } else {
                            firstPage = false;
                        }
                    default:
                        break;
                }
            }
        }
        // Rafraichissement de la page
        SDL_RenderClear(renderer);
        title.render(renderer, WIDTH / 2, 50);
        playTxt.render(renderer, WIDTH / 2,  HEIGHT / 7, menuSelection == 0);
        quitTxt.render(renderer, WIDTH / 2, 2 * HEIGHT / 7, menuSelection == 1);
        SDL_RenderPresent(renderer);
        if (gamePage) {
            Loop();
        }
    }
}

std::vector<Brick> * createBricksFromFile(SDL_Renderer* renderer, const std::string& filename, int brickWidth, int brickHeight, int windowWidth, int windowHeight) {
    std::vector<Brick> * bricks = new std::vector<Brick>;

    // Construire le chemin complet du fichier en utilisant le dossier "grilles"
    std::string filepath = "grilles/" + filename;

    // Vérifier si le fichier existe
    if (!std::__fs::filesystem::exists(filepath)) {
        std::cerr << "File does not exist: " << filepath << std::endl;
        return bricks;
    }

    // Ouvrir le fichier
    std::ifstream file(filepath);
    if (!file.is_open()) {
        std::cerr << "Unable to open file: " << filepath << std::endl;
        return bricks;
    }

    // Calculer la position y de la première ligne de briques
    int startY = 10;

    // Lire le fichier ligne par ligne
    std::string line;
    int y = 0;
    while (std::getline(file, line)) {
        // Calculer la position y de la ligne pour la centrer verticalement dans la fenêtre
        int lineY = startY + y * (brickHeight + 1);

        // Calculer l'espacement horizontal entre les briques
        int horizontalSpace = (windowWidth - line.size() * brickWidth) / (line.size() + 1);

        int x = 0;
        for (char c : line) {
            // Calculer la position x de la brique
            int brickX = horizontalSpace + x * (brickWidth + horizontalSpace);

            int brickY = lineY; // Position y de la brique
            switch (c) {
                case '0':
                    // Brique indestructible (blanche)
                    bricks->emplace_back(renderer, brickX, brickY, brickWidth, brickHeight, SDL_Color{255, 255, 255, 255}, -1);
                    break;
                default:
                    int hp = c - '0';
                    bricks->emplace_back(renderer, brickX, brickY, brickWidth, brickHeight, brickColors[hp], hp);
                    break;
            }
            x++;
        }
        y++;
    }

    // Fermer le fichier
    file.close();

    return bricks;
}


/*
 * Boucle principale de jeu.
 */
void GameLoop::Loop() {
    // Initialisation de la balle
    Ball b1;
    b1.velocity = {0, 1};
    b1.position = {320, 240};
    b1.speed = 10.0f;
    b1.color = {255, 0, 0, 255};

    // Initialisation de la plancha
    Paddle paddle(renderer, WIDTH / 2 - (PAD_W / 2), HEIGHT - 40, PAD_W, PAD_H);

    std::vector<Brick> * bricks = createBricksFromFile(renderer, "grille1.txt", 60, 20, WIDTH, HEIGHT); // Réglage de la largeur et de la hauteur des briques
    b1.bricks = bricks;
    b1.paddle = paddle;
    // Variables pour le calcul du temps
    Uint32 lastTime = SDL_GetTicks();
    const Uint32 targetFrameTime = 1000 / 60; // Cible de 60 images par seconde

    // Wait for the user to close the window
    bool quit = false;
    while (!quit) {
        // Calcul du temps écoulé depuis la dernière trame
        Uint32 currentTime = SDL_GetTicks();
        Uint32 elapsedTime = currentTime - lastTime;

        // Si le temps écoulé dépasse le temps cible pour une trame, effectuer une nouvelle trame
        if (elapsedTime >= targetFrameTime) {

            // Mettre à jour le temps de la dernière trame
            lastTime = currentTime;

            SDL_Event event;
            while (SDL_PollEvent(&event)) {
                switch (event.type) {
                    case SDL_QUIT:
                        quit = true;
                        break;
                    case SDL_KEYDOWN:
                        switch (event.key.keysym.sym) {
                            case SDLK_LEFT:
                                //paddle.moveLeft(PAD_SPEED , WIDTH);
                                paddle.velocity = {-1, 0};
                                break;
                            case SDLK_RIGHT:
                                //paddle.moveRight(PAD_SPEED , WIDTH);
                                paddle.velocity = {1, 0};
                                break;
                            case SDLK_ESCAPE:
                                std::cout << "Sortie du jeu." << std::endl;
                                quit = true;
                                break;
                            default:
                                break;
                        }
                        break;
                    case SDL_MOUSEMOTION:
                        // Déplacer la raquette en fonction de la position de la souris
                        paddle.setPosition(event.motion.x - PAD_W / 2, HEIGHT - 40);
                        break;
                    default:
                        paddle.velocity.x = 0;
                        break;
                }
            }
            b1.paddle = paddle;
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);

            // Mise à jour de l'affichage
            b1.draw(renderer);
            b1.updatePosition(WIDTH, HEIGHT);
            paddle.draw();
            paddle.updatePosition(PAD_SPEED, WIDTH);

            // Retrait des briques si elles n'ont plus de points de vie
            for (int i = bricks->size() - 1; i >= 0; --i) {
                if ((*bricks)[i].getHitPoints() <= 0) {
                    bricks->erase(bricks->begin() + i);
                }
            }
            // Dessiner les briques + Mise à jour de la couleur selon les points de vie de la brique
            for (auto& brick : *bricks) {
                brick.color = brickColors[brick.getHitPoints()];
                brick.draw();
            }

            SDL_RenderPresent(renderer);
        }
    }
}
