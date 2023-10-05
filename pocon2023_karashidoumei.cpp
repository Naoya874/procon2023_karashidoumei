#include <Windows.h>
#include <iostream>
#include <cpprest/http_client.h>

using namespace web;
using namespace web::http;
using namespace web::http::client;

pplx::task<void> Get()
{
    return pplx::create_task([]
        {
            // proxyあり
            //auto config = http_client_config();
            //config.set_proxy(web_proxy(utility::conversions::to_string_t("http://")));
            //http_client client(L"http://127.0.0.1:3000/matches/10?token=", config);

            http_client client(L"http://127.0.0.1:3000/matches/10?token=");
            return client.request(methods::GET);
        }).then([](http_response response)
            {
                if (response.status_code() == status_codes::OK)
                {
                    // レスポンスを文字列として取得後、標準出力する
                    auto body = response.extract_string();
                    std::wcout << body.get().c_str() << std::endl;

                    // レスポンスをJSONとして解析する
                    return response.extract_json();
                }
            }).then([](json::value json)
                {
                    // タイトルだけ取得する
                    //std::wcout << json[L"title"].as_string() << std::endl;
                });
}

int main()
{
    // コマンドプロンプトの文字コードをUTF-8に設定する
    SetConsoleOutputCP(CP_UTF8);

    try
    {
        Get().wait();
    }
    catch (const std::exception& e)
    {
        std::cout << "Error " << e.what() << std::endl;
    }

    return 0;
}