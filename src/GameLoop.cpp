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
void::GameLoop::addBall(Ball& b){
    balls.push_back(b);
}

GameLoop::GameLoop(): win("Brick Breaker", WIDTH, HEIGHT) {
    defaultColor = {255, 255, 255, 255};  // Blanc
    selectedColor = {255, 0, 0, 255};  // Rouge
}

GameLoop::~GameLoop() {}

void GameLoop::FirstPageLoop() {
    Text title(win.getRenderer(), defaultColor, "Brick Breaker", win.getDefaultFont());
    SelectableText playTxt(win.getRenderer(), defaultColor, selectedColor, "Play", win.getDefaultFont(), win.getSelectedFont());
    SelectableText quitTxt(win.getRenderer(), defaultColor, selectedColor, "Quit", win.getDefaultFont(), win.getSelectedFont());
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
                        win.present();
                    break;
                    case SDLK_DOWN:
                        std::cout << "Flèche bas pressée" << std::endl;
                        menuSelection = (menuSelection + 1) % 2;
                        win.present();
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
        win.clear();
        title.render(WIDTH / 2, 50);
        playTxt.render(WIDTH / 2,  HEIGHT / 7, menuSelection == 0);
        quitTxt.render(WIDTH / 2, 2 * HEIGHT / 7, menuSelection == 1);
        win.present();
        if (gamePage) {
            Loop();
            gamePage = false;
            firstPage = true;
        }
    }
}

std::shared_ptr<std::vector<Brick>> createBricksFromFile(const std::shared_ptr<SDL_Renderer>& renderer, const std::string& filename, int brickWidth, int brickHeight, int windowWidth, int windowHeight) {
    // Créer le vecteur de briques avec std::make_shared
    auto bricks = std::make_shared<std::vector<Brick>>();

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
    
    // Initialisation de la plancha
    Paddle paddle(win.getRenderer(), WIDTH / 2 - (PAD_W / 2), HEIGHT - 40, PAD_W, PAD_H);

    std::shared_ptr<std::vector<Brick>> bricks = createBricksFromFile(win.getRenderer(), "grille1.txt", 60, 20, WIDTH, HEIGHT);

    // Initialisation de la balle
    Ball b1(paddle,bricks);

    addBall(b1);

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
                                balls.clear();
                                //delete bricks;
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
            
            win.clear();

            // Mise à jour de l'affichage
            for (int i = 0; i < balls.size(); ++i) {
                if (balls[i].isOut(HEIGHT - 10)) {
                    // std::cout << "out" << std::endl;
                    balls.erase(balls.begin() + i);
                } else {
                    balls[i].setPaddle(paddle);
                    balls[i].draw(win.getRenderer());
                    balls[i].updatePosition(WIDTH, HEIGHT);
                }
            }

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
                brick.setColor(brickColors[brick.getHitPoints()]);
                brick.draw();
            }

            if(balls.empty()){
                quit = true;
            }

            win.present();
        }
    }
}
