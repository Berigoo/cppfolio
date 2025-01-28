#include "ControllerBlog.h"

static void view (const httplib::Request& req, httplib::Response& res);
static void get (const httplib::Request& req, httplib::Response& res);
static bool greaterThan1(const Views& view);

extern Container<Views> g_views;

ControllerBlog::ControllerBlog () {
  registerCallback("view", view);
  registerCallback("get", get);
}

void view (const httplib::Request& req, httplib::Response& res) {
  nlohmann::json j;
  j["views"] = nlohmann::json::array();
  g_views.json(j["views"]);
  res.set_content(Parser::parse(Path::relative("src/views/pages/Blog.html"), j), "text/html");
}

void get (const httplib::Request& req, httplib::Response& res) {
  auto id = req.matches[1];
  std::optional<Views> page = g_views.find(std::stoi(id));
  if (page.has_value()) {
    res.set_content(Parser::parse(page.value()["path"]), "text/html");
  } else {
    res.status = 404;
    res.reason = "Not Found";
  }
}

bool greaterThan1(const Views& view) {
  if (view["id"] > 1) {
    return true;
  } else {
    return false;
  }
}
