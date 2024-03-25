#include "interface.h"

void Interface::Show() {
  char val = 'g';
  SplashScreen();
  while (val != '0') {
    switch (val) {
      case '1':
        val = LoadFile();
        break;
      case '2':
        val = ExportFile();
        break;
      case '3':
        val = DepthAlgo();
        break;
      case '4':
        val = BreadthAlgo();
        break;
      case '5':
        val = Dijkstra();
        break;
      case '6':
        val = Warshall();
        break;
      case '7':
        val = Prima();
        break;
      case '8':
        val = AntManar();
        break;
      case 'g':
        val = WelcomePage();
        break;
      default:
        std::cout << "Вы ввели неверное значение, попробуйте еще раз\n";
        std::cin >> val;
        break;
    }
  }
}

void Interface::SplashScreen() {
  std::string greetings =
      "\t \033[102mДОБРО ПОЖАЛОВАТЬ В ПРИЛОЖЕНИЕ ДЛЯ "
      "РАБОТЫ С ГРАФАМИ\033[49m\n";
  std::string line1 =
      "\033[96m* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * "
      "* * \n"
      " * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * "
      "*\033[39m\n";
  std::string line2 =
      "\033[96m * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * "
      "* * *\n"
      "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * "
      "\033[39m\n";

  for (int i = 0; i < 30; ++i) {
    system("clear");
    std::cout << "\n\n\n\n\n";
    std::cout << (i % 2 == 0 ? line1 : line2);
    std::cout << greetings;
    std::cout << (i % 2 == 0 ? line2 : line1);
    std::this_thread::sleep_for(std::chrono::milliseconds(150));
  }
  system("clear");
  std::this_thread::sleep_for(std::chrono::milliseconds(300));
}

char Interface::WelcomePage() {
  char res;
  system("clear");
  std::cout << menu_;
  std::cout << "Выбирите действие:\n\n";
  std::cout << "\t\033[93m1\033[39m Загрузить граф из файла.\n";
  std::cout << "\t\033[93m2\033[39m Экспорт графа в dot файл.\n";
  std::cout
      << "\t\033[93m3\033[39m Обход графа в глубину от заданной вершины.\n";
  std::cout
      << "\t\033[93m4\033[39m Обход графа в ширину от заданной вершины.\n";
  std::cout << "\t\033[93m5\033[39m Поиск кратчайшего пути между двумя "
               "вершинами, алгоритм Дэйкстры.\n";
  std::cout << "\t\033[93m6\033[39m Поиск кратчайших путей между всеми парами "
               "вершин, алгоритм Флойда-Уоршелла.\n";
  std::cout << "\t\033[93m7\033[39m Поиск наименьшего оставного дерева, "
               "алгоритм Прима.\n";
  std::cout << "\t\033[93m8\033[39m Ршение задачи коммивояжера с помощью "
               "муравьиного алгоритма.\n";
  std::cout << "\t\033[93m0\033[39m \033[91mВыход из приложения.\033[39m\n\n";
  std::cin >> res;
  return res;
}

char Interface::LoadFile() {
  char res = 'f';
  std::string path;
  graph_ = new Graph();
  system("clear");
  std::cout << "\033[92mЗагрузка графа из файла:\033[39m\n\n";
  std::cout << "\t Введите путь до файла и имя файла: - \033[93m";
  std::cin >> path;
  std::cout << "\033[39m";
  try {
    graph_->LoadGraphFromFile(path);
    std::cout << "\nГраф успешно загружен.\n\n";
    PrintResultMat(graph_->GetMatrix());
    res = 'g';
    std::cout << "\n\nНажмите \033[94m\"ВВОД\"\033[39m чтобы продолжить.";
    std::cin.ignore();
    std::cin.get();
  } catch (const std::logic_error &e) {
    system("clear");
    std::cout << "\t\033[101mERROR: Что то пошло не так!\033[49m\n";
    std::cout << "\nНажмите 'Y' что бы попробовать снова или 'N' для выхода "
                 "обратно в меню\n";
    std::cin >> res;
    if (res == 'y' || res == 'Y')
      res = LoadFile();
    else
      res = 'g';
  }
  return res;
}

char Interface::ExportFile() {
  char res = 'f';
  std::string path;
  system("clear");
  std::cout << "\033[92mЭкспорт графа в DOT - файл:\033[39m\n\n";
  std::cout << "\t Введите путь до файла и имя файла: - \033[93m";
  std::cin >> path;
  std::cout << "\033[39m";
  try {
    graph_->ExportGraphToDot(path);
    std::cout << "\nГраф успешно экспортирован.\n\n";
    res = 'g';
    std::cout << "\n\nНажмите \033[94m\"ВВОД\"\033[39m чтобы продолжить.";
    std::cin.ignore();
    std::cin.get();
  } catch (const std::logic_error &e) {
    system("clear");
    std::cout << "\t\033[101mERROR: Что то пошло не так!\033[49m\n";
    std::cout << "\nНажмите 'Y' что бы попробовать снова или 'N' для выхода "
                 "обратно в меню\n";
    std::cin >> res;
    if (res == 'y' || res == 'Y')
      res = ExportFile();
    else
      res = 'g';
  }
  return res;
}

char Interface::DepthAlgo() {
  char res = 'f';
  int vertex = 0;
  graal_ = new GraphAlgorithms();
  system("clear");
  std::cout << "\033[92mОбход графа в глубину:\033[39m\n\n";
  std::cout << "Введите номер вершины: - \033[93m";
  try {
    std::cin >> vertex;
    std::cout << "\033[93m";
    auto result = graal_->DepthFirstSearch(*graph_, vertex);
    PrintDepthAndBreadthResult(result, 'd');
    res = 'g';
    std::cout << "\n\nНажмите \033[94m\"ВВОД\"\033[39m чтобы продолжить.";
    std::cin.ignore();
    std::cin.get();
  } catch (...) {
    system("clear");
    std::cout << "\t\033[101mERROR: Что то пошло не так!\033[49m\n";
    std::cout << "\nНажмите 'Y' что бы попробовать снова или 'N' для выхода "
                 "обратно в меню\n";
    std::cin >> res;
    if (res == 'y' || res == 'Y')
      res = DepthAlgo();
    else
      res = 'g';
  }
  return res;
}

char Interface::BreadthAlgo() {
  char res = 'f';
  int vertex = 0;
  graal_ = new GraphAlgorithms();
  system("clear");
  std::cout << "\033[92mОбход графа в ширину:\033[39m\n\n";
  std::cout << "Введите номер вершины: - \033[93m";
  try {
    std::cin >> vertex;
    std::cout << "\033[39m";
    auto result = graal_->BreadthFirstSearch(*graph_, vertex);
    PrintDepthAndBreadthResult(result, 'b');
    res = 'g';
    std::cout << "\n\nНажмите \033[94m\"ВВОД\"\033[39m чтобы продолжить.";
    std::cin.ignore();
    std::cin.get();
  } catch (...) {
    system("clear");
    std::cout << "\t\033[101mERROR: Что то пошло не так!\033[49m\n";
    std::cout << "\nНажмите 'Y' что бы попробовать снова или 'N' для выхода "
                 "обратно в меню\n";
    std::cin >> res;
    if (res == 'y' || res == 'Y')
      res = BreadthAlgo();
    else
      res = 'g';
  }
  return res;
}

char Interface::Dijkstra() {
  char res = 'f';
  unsigned v1, v2;
  graal_ = new GraphAlgorithms();
  system("clear");
  std::cout
      << "\033[92mПоиск кратчайшего пути между двумя вершинами:\033[39m\n\n";
  std::cout << "\t Введите через пробел номера вершин, чтобы узнать кратчайший "
               "путь между ними: \033[93m";
  try {
    std::cin >> v1 >> v2;
    std::cout << "\033[39m";
    auto result = graal_->GetShortestPathBetweenVertices(*graph_, v1, v2);
    std::cout << "Кратчайший путь между вершинами " << v1 << " и " << v2
              << " займет: - \033[95m" << result << "\033[39m";
    res = 'g';
    std::cout << "\n\nНажмите \033[94m\"ВВОД\"\033[39m чтобы продолжить.";
    std::cin.ignore();
    std::cin.get();
  } catch (...) {
    system("clear");
    std::cout << "\t\033[101mERROR: Что то пошло не так!\033[49m\n";
    std::cout << "\nНажмите 'Y' что бы попробовать снова или 'N' для выхода "
                 "обратно в меню\n";
    std::cin >> res;
    if (res == 'y' || res == 'Y')
      res = Dijkstra();
    else
      res = 'g';
  }
  return res;
}

char Interface::Warshall() {
  char res = 'f';
  graal_ = new GraphAlgorithms();
  system("clear");
  std::cout << "\033[92mПоиск кратчайшего пути между всеми вершинами:\n\n";
  try {
    auto result = graal_->GetShortestPathsBetweenAllVertices(*graph_);
    std::cout << "Матрица кратчайших путей:\033[39m\n\n";
    PrintResultMat(result);
    res = 'g';
    std::cout << "\n\nНажмите \033[94m\"ВВОД\"\033[39m чтобы продолжить.";
    std::cin.ignore();
    std::cin.get();
  } catch (...) {
    system("clear");
    std::cout << "\t\033[101mERROR: Что то пошло не так!\033[49m\n";
    std::cout << "\nНажмите 'Y' что бы попробовать снова или 'N' для выхода "
                 "обратно в меню\n";
    std::cin >> res;
    if (res == 'y' || res == 'Y')
      res = Warshall();
    else
      res = 'g';
  }
  return res;
}

char Interface::Prima() {
  char res = 'f';
  graal_ = new GraphAlgorithms();
  system("clear");
  std::cout << "\033[92mПоиск наименьшего оставного дерева:\n\n";
  try {
    auto result = graal_->GetLeastSpanningTree(*graph_);
    std::cout << "Матрица оставного дерева:\033[39m\n\n";
    PrintResultMat(result);
    res = 'g';
    std::cout << "\n\nНажмите \033[94m\"ВВОД\"\033[39m чтобы продолжить.";
    std::cin.ignore();
    std::cin.get();
  } catch (...) {
    system("clear");
    std::cout << "\t\033[101mERROR: Что то пошло не так!\033[49m\n";
    std::cout << "\nНажмите 'Y' что бы попробовать снова или 'N' для выхода "
                 "обратно в меню\n";
    std::cin >> res;
    if (res == 'y' || res == 'Y')
      res = Prima();
    else
      res = 'g';
  }
  return res;
}

char Interface::AntManar() {  // надо закончить!
  char res = 'f';
  graal_ = new GraphAlgorithms();
  system("clear");
  std::cout << "\033[92mРшение задачи коммивояжера:\n\n";
  try {
    auto result = graal_->SolveTravelingSalesmanProblem(*graph_);
    std::cout << "Решение задачи:\033[39m\n\n";
    PrintTsmResult(result);
    res = 'g';
    std::cout << "\n\nНажмите \033[94m\"ВВОД\"\033[39m чтобы продолжить.";
    std::cin.ignore();
    std::cin.get();
  } catch (...) {
    system("clear");
    std::cout << "\t\033[101mERROR: Что то пошло не так!\033[49m\n";
    std::cout << "\nНажмите 'Y' что бы попробовать снова или 'N' для выхода "
                 "обратно в меню\n";
    std::cin >> res;
    if (res == 'y' || res == 'Y')
      res = Prima();
    else
      res = 'g';
  }
  return res;
}

void Interface::PrintDepthAndBreadthResult(const std::vector<int> &vec,
                                           const char c) {
  system("clear");
  if (c == 'd') std::cout << "\033[92mОбход графа в глубину:\n\n";
  if (c == 'b') std::cout << "\033[92mОбход графа в ширину:\n\n";

  std::cout << "\tПорядок обхода: - \033[95m";
  for (auto v : vec) {
    std::cout << std::setw(3) << std::left << v << " ";
  }
  std::cout << "\033[39m";
}

void Interface::PrintResultMat(const std::vector<std::vector<int>> &vec) {
  std::cout << "\033[95m";
  for (const auto &row : vec) {
    for (const auto &col : row) {
      if (col == INF)
        std::cout << std::setw(3) << std::left << "INF ";
      else {
        if (!col) {
          std::cout << "\033[39m";
          std::cout << std::setw(3) << std::left << col << " ";
          std::cout << "\033[95m";
        } else {
          std::cout << std::setw(3) << std::left << col << " ";
        }
      }
    }
    std::cout << std::endl;
  }
  std::cout << "\033[39m";
}

void Interface::PrintTsmResult(const TsmResult &resStruct) {
  std::cout << "\t\033[92mОптимальный путь: - \033[95m";
  for (auto v : resStruct.vertices) {
    std::cout << std::setw(3) << std::left << v << " ";
  }
  std::cout << "\n\t\033[92mДистанция: - \033[95m" << resStruct.distance
            << "\033[39m";
}
