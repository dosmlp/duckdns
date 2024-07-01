#define CPPHTTPLIB_OPENSSL_SUPPORT
#include <iostream>
#include <fstream>
#include <format>
#include "httplib.h"
#include "json.hpp"
using json = nlohmann::json;

void updateIpv6(const std::string& domain,const std::string& token,const std::string& ip)
{
    std::string update_url = std::format(R"(/update?domains={}&token={}&ipv6={}&verbose=true)",domain,token,ip);

    httplib::Client ucli("https://www.duckdns.org");
    httplib::Result ures = ucli.Get(update_url);
    std::cout << ures->body <<"\n";
}
void updateIpv4(const std::string& domain,const std::string& token,const std::string& ip)
{
    std::string update_url = std::format(R"(/update?domains={}&token={}&ipv4={}&verbose=true)",domain,token,ip);

    httplib::Client ucli("https://www.duckdns.org");
    httplib::Result ures = ucli.Get(update_url);
    std::cout << ures->body <<"\n";
}

int main(int argc,char* argv)
{
    std::ifstream cfg_file("cfg.json");
    json root = json::parse(cfg_file,nullptr,false);
    if (root.is_discarded() || root.empty()) {
        std::cerr << "cfg error\n";
        return 0;
    }
    auto token = root.value("token","");
    auto domain = root.value("domain","");

    std::cout << "hello duckdns!\n";

    httplib::Client cliv6("https://text.ipv6.myip.wtf");
    httplib::Result resv6 = cliv6.Get("/");
    std::string ipv6 = resv6->body;
    ipv6.erase(ipv6.length()-1,1);

    httplib::Client cliv4("https://text.ipv4.myip.wtf");
    httplib::Result resv4 = cliv4.Get("/");
    std::string ipv4 = resv4->body;
    ipv4.erase(ipv4.length()-1,1);

    updateIpv6(domain,token,ipv6);

    return 0;
}