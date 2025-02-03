#include "ControllerBlog.h"
#include "nlohmann/json_fwd.hpp"

static void view (const httplib::Request& req, httplib::Response& res);
static void get (const httplib::Request& req, httplib::Response& res);

static bool getByTag(const Views& view);

extern Container<Views> g_views;
extern inja::Environment g_templates;

static std::string sIndexBlogContent;

ControllerBlog::ControllerBlog () {
  std::ifstream file(Path::relative("src/views/pages/Blog.html"));
  assert(file.is_open());       //TODO
  std::stringstream ss;
  ss << file.rdbuf();
  sIndexBlogContent = ss.str();
  

  registerCallback("view", view);
  registerCallback("get", get);
}

void view (const httplib::Request& req, httplib::Response& res) {
  nlohmann::json j;
  j["views"] = nlohmann::json::array();
  j["tag"] = nullptr;

  Container<Views> v;
  if (req.has_param("tag")) {
      std::string tag = req.get_param_value("tag");
      j["tag"] = tag;
      auto byTag = [&](const Views& view) {
        auto vec = (view["tags"].get<std::vector<std::string>>());
        auto it = std::find(vec.begin(), vec.end(), tag);

        if (it != vec.end()) {
          return true;
        } else {
          return false;
        }
      };
      v = g_views.get(byTag);
  } else {
    v = g_views;
  }
  v.json(j["views"]);

  res.set_content(g_templates.render(sIndexBlogContent, j), "text/html");
}

void get (const httplib::Request& req, httplib::Response& res) {
  auto id = req.matches[1];
  Views* page = g_views.find(std::stoi(id));
  if (page) {
    res.set_content(g_templates.render(page->getContent(), nullptr), "text/html");
  } else {
    res.status = 404;
    res.reason = "Not Found";
  }
}
