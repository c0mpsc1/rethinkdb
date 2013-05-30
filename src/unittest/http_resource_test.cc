#include "unittest/gtest.hpp"

#include "http/http.hpp"

namespace unittest {

void RunThrowingResourceTest(const char *path) {
    bool caught_exception = false;
    try {
        http_req_t::resource_t resource(path);
        auto it = resource.begin();
        auto jt = resource.end();
    } catch (const std::invalid_argument &ex) {
        caught_exception = true;
    }

    ASSERT_TRUE(caught_exception);
}

TEST(HttpResourceTest, EmptyPath) {
    RunThrowingResourceTest("");
}

TEST(HttpResourceTest, DoesNotStartWithSlash) {
    RunThrowingResourceTest("foo/");
}

TEST(HttpResourceTest, Slash) {
    const char *str = "/";
    http_req_t::resource_t resource(str);
    auto it = resource.begin();
    auto jt = resource.end();
    ASSERT_EQ(it, jt);
    ASSERT_EQ(str, resource.as_string());
}

TEST(HttpResourceTest, OneElt) {
    const char *str = "/foo";
    http_req_t::resource_t resource(str);
    auto it = resource.begin();
    auto jt = resource.end();
    ASSERT_EQ("foo", *it);
    ++it;
    ASSERT_EQ(jt, it);
    ASSERT_EQ(str, resource.as_string());
}

TEST(HttpResourceTest, OneEltSlash) {
    const char *str = "/foo/";
    http_req_t::resource_t resource(str);
    auto it = resource.begin();
    auto jt = resource.end();
    ASSERT_EQ("foo", *it);
    ++it;
    ASSERT_NE(jt, it);
    ASSERT_EQ("", *it);
    ++it;
    ASSERT_EQ(jt, it);
    ASSERT_EQ(str, resource.as_string());
}

TEST(HttpResourceTest, TwoElt) {
    const char *str = "/foo/bar";
    http_req_t::resource_t resource(str);
    auto it = resource.begin();
    auto jt = resource.end();
    ASSERT_EQ("foo", *it);
    ++it;
    ASSERT_EQ("bar", *it);
    ++it;
    ASSERT_EQ(jt, it);
    ASSERT_EQ(str, resource.as_string());
}

TEST(HttpResourceTest, TwoEltSlash) {
    const char *str = "/foo/bar/";
    http_req_t::resource_t resource(str);
    auto it = resource.begin();
    auto jt = resource.end();
    ASSERT_EQ("foo", *it);
    ++it;
    ASSERT_EQ("bar", *it);
    ++it;
    ASSERT_NE(jt, it);
    ASSERT_EQ("", *it);
    ++it;
    ASSERT_EQ(jt, it);
    ASSERT_EQ(str, resource.as_string());
}

TEST(HttpResourceTest, TwoEltSlashSlash) {
    const char *str = "/foo/bar//";
    http_req_t::resource_t resource(str);
    auto it = resource.begin();
    auto jt = resource.end();
    ASSERT_EQ("foo", *it);
    ++it;
    ASSERT_EQ("bar", *it);
    ++it;
    ASSERT_NE(jt, it);
    ASSERT_EQ("", *it);
    ++it;
    ASSERT_NE(jt, it);
    ASSERT_EQ("", *it);
    ++it;
    ASSERT_EQ(jt, it);
    ASSERT_EQ(str, resource.as_string());
}


TEST(HttpResourceTest, TwoEltSlashSlashSlash) {
    const char *str = "/foo/bar///";
    http_req_t::resource_t resource(str);
    auto it = resource.begin();
    auto jt = resource.end();
    ASSERT_EQ("foo", *it);
    ++it;
    ASSERT_EQ("bar", *it);
    ++it;
    ASSERT_NE(jt, it);
    ASSERT_EQ("", *it);
    ++it;
    ASSERT_NE(jt, it);
    ASSERT_EQ("", *it);
    ++it;
    ASSERT_NE(jt, it);
    ASSERT_EQ("", *it);
    ++it;
    ASSERT_EQ(jt, it);
    ASSERT_EQ(str, resource.as_string());
}

TEST(HttpResourceTest, TwoEltSlashSlashElt) {
    const char *str = "/foo/bar//baz";
    http_req_t::resource_t resource(str);
    auto it = resource.begin();
    auto jt = resource.end();
    ASSERT_EQ("foo", *it);
    ++it;
    ASSERT_EQ("bar", *it);
    ++it;
    ASSERT_NE(jt, it);
    ASSERT_EQ("", *it);
    ++it;
    ASSERT_EQ("baz", *it);
    ++it;
    ASSERT_EQ(jt, it);
    ASSERT_EQ(str, resource.as_string());
}

TEST(HttpResourceTest, SlashSlash) {
    const char *str = "//";
    http_req_t::resource_t resource(str);
    auto it = resource.begin();
    auto jt = resource.end();
    ASSERT_NE(jt, it);
    ASSERT_EQ("", *it);
    ++it;
    ASSERT_NE(jt, it);
    ASSERT_EQ("", *it);
    ++it;
    ASSERT_EQ(jt, it);
    ASSERT_EQ(str, resource.as_string());
}

TEST(HttpResourceTest, SubResource) {
    http_req_t::resource_t resource("/foo/bar/baz");
    ASSERT_EQ("/foo/bar/baz", resource.as_string());
    auto it = resource.begin();
    ASSERT_EQ("foo", *it);
    ++it;
    http_req_t::resource_t subresource(resource, it);
    ASSERT_EQ("/bar/baz", subresource.as_string());
    auto jt = subresource.begin();
    auto kt = subresource.end();
    ASSERT_EQ("bar", *jt);
    ++jt;
    ASSERT_EQ("baz", *jt);
    ++jt;
    ASSERT_EQ(kt, jt);
}


}  // namespace unittest
