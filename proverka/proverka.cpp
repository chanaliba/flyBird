#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <string>


#define WIDTH 1000 /*ширина окна*/
#define HEIGHT 600 /*высота окна*/
using namespace sf;

class MainWindow :public RenderWindow
{
    int state = 0;
    std::vector<Texture> images; /*массив картинок*/
    std::vector<Sprite> sprites; /*массив спрайтов*/
    std::vector <SoundBuffer> buf; /*буферный массив звуков*/
    std::vector <Sound> sounds; /*массив звуков*/
    Font font; 
    bool quit = false;
    Clock mainTimer;
    Text mainTitle;
public:

    MainWindow(VideoMode vm, std::string str);
    void DrawKukushka(int x, int y); /*функция отрисовки кукушки*/
    void DrawBook(int x, int y); /*функция отрисовка препятствия*/
    void DrawBackground(); /*функция отрисовки фона игры*/
    void DrawRules(); /*функция отрисовка правил игры*/
    void DrawRectRules(); /*функция отрисовки выбора правил*/
    void DrawRectStart(); /*функуия отрисовки выбора старта игры*/
    void DrawGO(); /*функция отрисовки проигрыша*/
    void DrawWIN(); /*функция отрисовки выигрыша*/
    void DrawMenu(); /*функция отрисовки меню*/
    void Menu(MainWindow&); /*реализация работы меню*/
    void FlyKukushka(MainWindow&); /*реализация игры*/
    void PollEvents(); /*функция отслеживания событий пользователя*/  
    bool collision(int xFirst, int yFirst, int heightFirst, int widthFirst, int xSecond, int ySecond, int heightSecond, int widthSecond); /*функция обработки коллизий*/
    bool IsItTimeYet(int time)
    {
        if (time > 25)
            return true;
        return false;
    };

};

MainWindow::MainWindow(VideoMode vm, std::string str) :RenderWindow(vm, str) /*конструктор класса*/
{
    setFramerateLimit(60);

    /*загружаем все текстуры в массив картинок*/
    Texture tmp; 
    if (!tmp.loadFromFile("background_WIN.jpg"))
        throw "Error";
    images.push_back(tmp);
    if (!tmp.loadFromFile("background_GO.jpg"))
        throw "Error";
    images.push_back(tmp);
    if (!tmp.loadFromFile("background_menu_rules.jpg"))
        throw "Error";
    images.push_back(tmp);
    if (!tmp.loadFromFile("background_menu_start.jpg"))
        throw "Error";
    images.push_back(tmp);
    if (!tmp.loadFromFile("background_rules.png"))
        throw "Error";
    images.push_back(tmp);
    if (!tmp.loadFromFile("background_menu.jpg"))
        throw "Error";
    images.push_back(tmp);    
    if (!tmp.loadFromFile("background.jpg"))
        throw "Error";
    images.push_back(tmp);
    if (!tmp.loadFromFile("prepyatstvie.png"))
        throw "Error";
    images.push_back(tmp);
    if (!tmp.loadFromFile("kukushkasprite.png"))
        throw "Error";
    images.push_back(tmp); 

    /*загружаем все картинки спрайтами и закидываем в массив спрайтов для дальнейшей работы с ними*/
    Sprite bckg_WIN;
    bckg_WIN.setTexture(images[0]);
    bckg_WIN.setScale(getSize().x / bckg_WIN.getLocalBounds().width, getSize().y / bckg_WIN.getLocalBounds().height);
    sprites.push_back(bckg_WIN);

    Sprite bckg_GO;
    bckg_GO.setTexture(images[1]);
    bckg_GO.setScale(getSize().x / bckg_GO.getLocalBounds().width, getSize().y / bckg_GO.getLocalBounds().height);
    sprites.push_back(bckg_GO);

    Sprite bckg_menu_rules;
    bckg_menu_rules.setTexture(images[2]);
    bckg_menu_rules.setScale(getSize().x / bckg_menu_rules.getLocalBounds().width, getSize().y / bckg_menu_rules.getLocalBounds().height);
    sprites.push_back(bckg_menu_rules);

    Sprite bckg_menu_start;
    bckg_menu_start.setTexture(images[3]);
    bckg_menu_start.setScale(getSize().x / bckg_menu_start.getLocalBounds().width, getSize().y / bckg_menu_start.getLocalBounds().height);
    sprites.push_back(bckg_menu_start);

    Sprite bckg_rules;
    bckg_rules.setTexture(images[4]);
    bckg_rules.setScale(getSize().x / bckg_rules.getLocalBounds().width, getSize().y / bckg_rules.getLocalBounds().height);
    sprites.push_back(bckg_rules);

    Sprite bckg_menu;
    bckg_menu.setTexture(images[5]);
    bckg_menu.setScale(getSize().x / bckg_menu.getLocalBounds().width, getSize().y / bckg_menu.getLocalBounds().height);
    sprites.push_back(bckg_menu);

    Sprite bckg;
    bckg.setTexture(images[6]);
    bckg.setScale(getSize().x / bckg.getLocalBounds().width, getSize().y / bckg.getLocalBounds().height);
    sprites.push_back(bckg);

    Sprite kuku;
    kuku.setTexture(images[7]);
    kuku.setScale(0.5, 0.5);
    kuku.setPosition(400, 400);
    sprites.push_back(kuku);
    kuku.setTexture(images[8]);
    kuku.setTextureRect(IntRect(0, 0, images[8].getSize().x / 2, images[8].getSize().y));
    kuku.setScale(0.35, 0.35);
    sprites.push_back(kuku);
    kuku.setTextureRect(IntRect(images[8].getSize().x / 2, 0, images[8].getSize().x, images[8].getSize().y));
    kuku.setScale(0.35, 0.35);
    sprites.push_back(kuku);

    /*загружаем звук в массив звуков*/
    SoundBuffer tmpbuf;
    if (!tmpbuf.loadFromFile("tada.mp3"))
        throw "Error";
    buf.push_back(tmpbuf);
    Sound tmpsound;
    tmpsound.setBuffer(buf[0]);
    sounds.push_back(tmpsound);

    /*задаем параметры тексту*/
    if (!font.loadFromFile("OpenSans-SemiBold.ttf"))
        throw "Error";
    mainTitle.setFont(font);
    mainTitle.setFillColor(Color::Black);
    mainTitle.setStyle(Text::Bold);
}



void MainWindow::DrawKukushka(int x, int y) /*отрисовка кукушки по координатам*/
{
    int ind = state / 10 + 8;
    sprites[ind].setPosition(x, y);
    draw(sprites[ind]);
    state = (state + 1) % 20;
}

void MainWindow::DrawBackground() /*фон игры*/
{
    draw(sprites[6]);
    draw(mainTitle);
}

void MainWindow::DrawRules() /*правила игры*/
{
    draw(sprites[4]);
}

void MainWindow::DrawRectRules() /*выбор правил*/
{
    draw(sprites[2]);
}

void MainWindow::DrawRectStart() /*выбор старта*/
{
    draw(sprites[3]);
}

void MainWindow::DrawGO() /*проигрыш*/
{
    draw(sprites[1]);
    draw(mainTitle);
}

void MainWindow::DrawWIN() /*выигрыш*/
{
    draw(sprites[0]);
    draw(mainTitle);
}

void MainWindow::DrawBook(int x, int y) /*открисовка препятствия по координатам*/
{
    sprites[7].setPosition(x, y);
    draw(sprites[7]);
}

void MainWindow::DrawMenu() /*меню*/
{
    draw(sprites[5]);
}

void MainWindow::Menu(MainWindow& window) /*реализация работы меню*/
{
    while (!quit)
    {
        PollEvents(); /*ловим события*/
        int time = mainTimer.getElapsedTime().asMilliseconds(); /*отсчет времени для таймера игры*/
        if (IsItTimeYet(time))
        {
            DrawMenu(); /*рисуем меню*/
            
            /*если выбрали кнопку старт - начинаем игру */
            if (IntRect(67, 60, 383, 130).contains(Mouse::getPosition(window)))  
            {
                DrawRectStart();
                if (Mouse::isButtonPressed(Mouse::Left))
                {
                    FlyKukushka(window);
                }
            }
            
            /*если выбрали кнопку правил - выводим правила на экран*/
            if (IntRect(67, 248, 383, 130).contains(Mouse::getPosition(window)))
            {
                DrawRectRules();
                if (Mouse::isButtonPressed(Mouse::Left))
                    DrawRules();
            }

            display(); /*отрисовываем заново окно*/
            clear();
            mainTimer.restart(); /*перезапуск таймера*/
        }
    }

}

void MainWindow::FlyKukushka(MainWindow& window) /*реализация игры*/
{
    Clock clock; /*для таймера*/

    /*задаем ширину и высоту кукушки, понадобится для обработки столкновений*/
    int widthKukushka = sprites[6].getLocalBounds().width * 0.1; 
    int heightKukushka = sprites[6].getLocalBounds().height * 0.1;


    /*ставим начальные координаты кукушки*/
    int xKukushka = 30;
    int yKukushka = HEIGHT/2;

    /*выставляем размеры препятствия и начальные координаты*/
    int widthBook1 = sprites[5].getLocalBounds().width * 0.3;
    int heightBook1 = sprites[5].getLocalBounds().height * 0.3;

    int xBook1 = WIDTH;
    int yBook1 = rand() % HEIGHT;

    int widthBook2 = sprites[5].getLocalBounds().width * 0.3;
    int heightBook2 = sprites[5].getLocalBounds().height * 0.3;

    int xBook2 = WIDTH;
    int yBook2 = rand() % HEIGHT;
    
    /*обнуляем таймер*/
    int timer = 0; 
    clock.restart();

    while (!quit)
    {
        PollEvents();
        int time = mainTimer.getElapsedTime().asMilliseconds(); 
        timer = clock.getElapsedTime().asSeconds(); /*изменяем таймер*/
        if (IsItTimeYet(time))
        {
            /*выводим новое значение таймера*/
            mainTitle.setCharacterSize(24);
            mainTitle.setPosition(WIDTH - 50, 10);
            mainTitle.setString(String(std::to_string(timer)));

            DrawBackground();
            /*если нажат пробел или лкм - кукушка летит вверх*/
            if (Keyboard::isKeyPressed(Keyboard::Space)) 
            {
                yKukushka -= 5;
                xKukushka += 1;
                sounds[0].play();
            }
            else if (Mouse::isButtonPressed(Mouse::Left))
            {
                yKukushka -= 5;
                xKukushka += 1;
                sounds[0].play();
            }
            else /*иначе она летит вниз*/
            {
                yKukushka += 2;
            }
            
            /*координата х кукушки изменяется рандомно*/
            xKukushka += 0.5 + (rand() % 3) / 2; 

            /*обработка выхода за пределы окна*/
            if (yKukushka < 0)
                yKukushka =  0;
            if (yKukushka > HEIGHT - heightKukushka)
                yKukushka = HEIGHT - heightKukushka;

            /*меняем положение препятствий*/
            xBook1 -= rand() % 10;
            xBook2 -= rand() % 7;

            /*если препятствие удачно долетело ло конца - обнуляем координаты*/
            if (xBook1 < -widthBook1)
            {
                xBook1 = WIDTH + widthBook1;
                yBook1 = rand() % (HEIGHT + heightBook1 + 100);
            }
            
            if (xBook2 < -widthBook2)
            {
                xBook2 = WIDTH + widthBook2;
                yBook2 = rand() % (HEIGHT + heightBook2 + 100);
            }

            /*отрисовка*/
            DrawBook(xBook1, yBook1);
            DrawBook(xBook2, yBook2);
            DrawKukushka(xKukushka, yKukushka);


            /*если кукушка долетела до конца - выводим победу и результат таймера*/
            if (xKukushka + widthKukushka == WIDTH)
            {
                clock.restart();
                float time = 0; /*таймер на задержку картинки*/
                DrawWIN();
                while (time <= 100) /*задерживаем картинку выигрыша*/
                {
                    window.clear(Color::White);
                    DrawWIN();

                    mainTitle.setCharacterSize(100);
                    mainTitle.setString(String(std::to_string(timer) + L" сек"));
                    mainTitle.setPosition(WIDTH / 2 - 75, HEIGHT / 2 + 15);

                    window.display();
                    time += clock.getElapsedTime().asSeconds();
                }
                Menu(window); /*выходим в меню*/
            }

            /*если произошло столкновение с препятствием*/
            if (collision(xKukushka, yKukushka, heightKukushka, widthKukushka, xBook1, yBook1, heightBook1, widthBook1) ||
                collision(xKukushka, yKukushka, heightKukushka, widthKukushka, xBook2, yBook2, heightBook2, widthBook2))
            {
                clock.restart();
                float time = clock.getElapsedTime().asSeconds(); /*обнуление таймера*/
                window.DrawGO(); /*отрисовка проигрыша*/
                while (time <= 100) /*задержка картинки*/
                {
                    window.clear(Color::White);
                    DrawGO();
                    
                    /*вывод результата*/
                    mainTitle.setCharacterSize(100);
                    mainTitle.setString(String(std::to_string(timer) + L" сек"));
                    mainTitle.setPosition(WIDTH / 2 - 75, HEIGHT / 2 + 15);

                    window.display();
                    time += clock.getElapsedTime().asSeconds();
                }
                Menu(window); /*выход в меню*/
            }

            display();
            clear();
            mainTimer.restart();
        }
    }

}

/*обработка коллизий*/
bool MainWindow::collision(int xFirst, int yFirst, int heightFirst, int widthFirst, int xSecond, int ySecond, int heightSecond, int widthSecond)
{
    if (xSecond <= xFirst + widthFirst && ySecond <= yFirst + heightFirst &&
        xFirst <= xSecond + widthSecond && yFirst <= ySecond + heightSecond)
    {
        return true;
    }
    return false;
}

/*ловим действия пользователя*/
void MainWindow::PollEvents()
{
    sf::Event event;
    while (pollEvent(event))
    {
        switch (event.type)
        {
        case Event::Closed: /*если нажата кнопка закрыть - выходим из программы*/
            quit = true;
            break;
        case Event::KeyPressed:
            if (event.key.scancode == Keyboard::Scan::Escape) /*выход из программы при нажатии esc*/
                quit = true;            
            break;
        default:
            break;
        }
    }
}

int main()
{
    srand(time(NULL));
    MainWindow window(VideoMode(WIDTH, HEIGHT), "Kukushka");
    while (window.isOpen())
    {
        window.clear(Color::White);
        window.Menu(window); /*запуск меню*/
        window.close();
    }
    return 0;
}
