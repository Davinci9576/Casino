#include "API.h"
#include "Player.h"
#include <curl/curl.h>
#include <string>
#include <iostream>
using namespace std;

static size_t WriteCallback(
    void* contents,
    size_t size,
    size_t nmemb,
    std::string* output)
{
    output->append(
        (char*)contents,
        size * nmemb
    );

    return size * nmemb;
}
void ApiService::sendScore(const Player& player)
{
    CURL* curl = curl_easy_init();

    if (curl)
    {
        string json =
            "{\"name\":\"" + player.getUsername() +
            "\",\"money\":" + to_string(player.getBalance()) + "}";

        curl_easy_setopt(curl,
            CURLOPT_URL,
            "https://poker-server-dcdu.onrender.com/score");

        curl_easy_setopt(curl,
            CURLOPT_POSTFIELDS,
            json.c_str());

        struct curl_slist* headers = NULL;

        headers = curl_slist_append(
            headers,
            "Content-Type: application/json"
        );

        curl_easy_setopt(curl,
            CURLOPT_HTTPHEADER,
            headers);

        curl_easy_perform(curl);

        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
    }
}
std::string ApiService::fetchLeaderboard()
{
    CURL* curl = curl_easy_init();

    std::string response;

    if (curl)
    {
        curl_easy_setopt(
            curl,
            CURLOPT_URL,
            "https://poker-server-dcdu.onrender.com/leaderboard"
        );

        curl_easy_setopt(
            curl,
            CURLOPT_WRITEFUNCTION,
            WriteCallback
        );

        curl_easy_setopt(
            curl,
            CURLOPT_WRITEDATA,
            &response
        );

        curl_easy_setopt(
            curl,
            CURLOPT_SSL_VERIFYPEER,
            0L
        );

        CURLcode res = curl_easy_perform(curl);

        if (res != CURLE_OK)
        {
            std::cout
                << "ERROR: "
                << curl_easy_strerror(res)
                << std::endl;
        }

        curl_easy_cleanup(curl);
    }

    return response;
}
bool ApiService::registerUser(
    const std::string& username,
    const std::string& password)
{
    CURL* curl = curl_easy_init();

    if (curl)
    {
        std::string json =
            "{\"username\":\"" + username +
            "\",\"password\":\"" + password + "\"}";

        curl_easy_setopt(
            curl,
            CURLOPT_URL,
            "https://poker-server-dcdu.onrender.com/register"
        );

        curl_easy_setopt(
            curl,
            CURLOPT_POSTFIELDS,
            json.c_str()
        );

        struct curl_slist* headers = NULL;

        headers = curl_slist_append(
            headers,
            "Content-Type: application/json"
        );

        curl_easy_setopt(
            curl,
            CURLOPT_HTTPHEADER,
            headers
        );

        CURLcode res = curl_easy_perform(curl);

        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);

        return (res == CURLE_OK);
    }

    return false;
}
bool ApiService::login(
    const std::string& username,
    const std::string& password)
{
    CURL* curl = curl_easy_init();

    if (curl)
    {
        std::string json =
            "{\"username\":\"" + username +
            "\",\"password\":\"" + password + "\"}";

        curl_easy_setopt(
            curl,
            CURLOPT_URL,
            "https://poker-server-dcdu.onrender.com/login"
        );

        curl_easy_setopt(
            curl,
            CURLOPT_POSTFIELDS,
            json.c_str()
        );

        struct curl_slist* headers = NULL;

        headers = curl_slist_append(
            headers,
            "Content-Type: application/json"
        );

        curl_easy_setopt(
            curl,
            CURLOPT_HTTPHEADER,
            headers
        );

        CURLcode res = curl_easy_perform(curl);

        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);

        return (res == CURLE_OK);
    }

    return false;
}