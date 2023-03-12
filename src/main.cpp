#include <iostream>
#include "ConverterJSON.h"
#include "InvertedIndex.h"
#include "SearchServer.h"

/**
 * Метод Записывает ответы в файл JSON answers.json
 * @param [in] allRequestsResults выдает результат поиска релевантных страниц
 */
void writeAnswers(const std::vector<std::vector<RelativeIndex>>& allRequestsResults)
{
    if (allRequestsResults.empty())
    {
        std::cout << "No matches are found.\n";
        return;
    }
    std::vector<std::vector<std::pair<int, float>>> allRequestsResultsReadyForJSON;
    for (auto& requestResult : allRequestsResults)
    {
        std::vector<std::pair<int, float>> requestResultReadyForJSON;
        for (auto& pageRelevance : requestResult)
        {
            std::pair<int, float> relevancePair;
            relevancePair.first = (int) pageRelevance.doc_id;

            relevancePair.second = pageRelevance.rank;

            requestResultReadyForJSON.push_back(relevancePair);
        }
        allRequestsResultsReadyForJSON.push_back(requestResultReadyForJSON);
    }
    ConverterJSON::getInstance()->putAnswers(allRequestsResultsReadyForJSON);

}

int main()
{
    //Инициализация:
    ConverterJSON::getInstance()->readConfigFile();
    ConverterJSON::getInstance()->readRequestFile();
    std::vector<std::string> documents = ConverterJSON::getInstance()->getTextDocuments();
    auto* invertedIndex = new InvertedIndex();
    invertedIndex->updateDocumentBase(documents);

    //Поиск
    std::cout << "Searching...\n";
    SearchServer searchServer(*invertedIndex);
    searchServer.setMaxResponses(ConverterJSON::getInstance()->getMaxResponses());
    auto allRequestsResults = searchServer.search(ConverterJSON::getInstance()->getRequests());
    writeAnswers(allRequestsResults);
    std::cout << "End of search.\n";
    delete invertedIndex;
    
    //Приостановить консоль - раскомментировать, если пауза необходима:
    std::cin.get();
    return 0;
}