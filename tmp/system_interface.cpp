// Результатом диссертации, как я понимаю, должен быть некий программный комплекс, который делает что-то умное с ключевыми словами
// Предположим, что он состоит из двух основных классов:
// TKeywordProcessor/TEntityProcessor - все, связанное с семантической близостью пары слов/наборов(сущностей) - 1 и 2 главы диссертации
// Пользователи классов решают свои важные задачи (поиск эксперта, кластеризация и прочее) с помощью этих классов - 3 глава диссертации

using kid = ui64; // keyword id
using eid = ui64; // entity id - сотрудники, лаборатории, проекты - что угодно

class TKeywordProcessor
{
public:
    void AddKeywords(map<eid, vector<kid>>); // добавляет коллекцию наборов слов
    void Fit(); // построить кучу графов, у которых слова в вершинах, собрать обучающие выборки, посчитать признаки, обучить модель
    void ComputeCluters(); // кластеризовать графы
    void BuildThesaurus(); // по обученной модели найти несколько похожих слов для каждого из имеющихся

    map<kid, kid> GetThesaurus(); 
    vector<kid> GetCluster(kid);
    kid GetHypernym(kid); // у меня вроде был алгоритм, который умеет автоматически нечто похожее на гиперонимы возвращать
    double ComputeSimilarity(kid, kid); // семантическая близость пары ключевых слов
private:
    TKeywordSimModel model;
};

class TEntityProcessor // главный класс, который делает основные вещи - как-то считает близости между сущностями
{
public:
    void AddKeywords(map<eid, vector<kid>>); // добавляет коллекцию ключевых слов, заодно прокидывает в kwProc
    void AddEntities(graph<eid, relationType>); // добавляет доп.графы взаимосвязей между объектами (про проекты, например)

    void Fit(); // подготовавливает все графы, у которых наборы в вершинах, вызывает kwProc.Fit().
                // Ну и прочие обучающие процедуры, активно использующие kwProc
    
    vector<kid> SuggestKeywords(eid); // предлагаем пользователю какой-то набор слоd (на случай, если, например, сам он не заполнил,
                                      // а мы по какой-то причине хотим ему помочь
    vector<eid> FindEntities(vector<kid>); // поиск эксперта - по запросу ключевых слов вернуть какие-то сущности
    double ComputeSimilarity(vector<kid>, vector<kid>) // семантическая близость между наборами
    double ComputeSimilarity(eid, eid); // семантическая близость между сущностями. Если считать, что eid задается набором kid, 
                                        // то просто вызываем прошлую функцию.
                                        // если один из eid пустой, то делаем SuggestKeywords
                                        // вообще не знаю, должны ли идеологически отличаться функции
                                        // близости пары сущностей и близости пары наборов ключевых слов, к ним прицепленным
                                        // в рамках нашей постановки задачи
private:
    TKeywordProcessor kwProc;
    TEntitySimModel model;
};
