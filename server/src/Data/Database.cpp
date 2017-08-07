
#include "Data/Database.h"

using namespace m2::server;


Database::Database(const std::string& rootDir)
    : Users(rootDir)
    , Dialogs(rootDir + "Dialogs/")
{}

bool
Database::CreateUser(uuids::uuid Uid, const std::string &PublicKey)
{ return Users.CreateUser(Uid, PublicKey) ? true : false; }

bool
Database::CreateUser(uuids::uuid Uid, std::string &&PublicKey)
{ return Users.CreateUser(Uid, std::move(PublicKey)); }


bool
Database::IsClienExists(uuids::uuid Uid)
{ return Users[Uid]; }


std::string
Database::getUserPublicKey(uuids::uuid Uid)
{ return Users(Uid).PublicKey(); }

std::string
Database::getPublicServerKey()
{ return "-----BEGIN PUBLIC KEY-----"
        "MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEA7hXrrlg3N9Uelmd8X3uT"
        "YyrunZwnBqb/RJ0srNxPd+PMe5Dasw39W6TMDcS7WYgeFIsdlIAfPzWeONKvdCnG"
        "INRIJClOHKQOPejAjfISKaCRrdiCBCQ9hvfqhd7yi9kbWTlkOYtddMceJjwWfEuO"
        "IBkaF1F03bOGKNQgXhEbCFTo8ow+F/lhz7MZXq+pWEpArXwSWFpigVHkAN+5acEY"
        "jX/4Pzg9jwrh3NJMffoeFTch3UGFxY5oQShSGeqFqP4uCb2DvZjNu/aBJxNQHSPz"
        "tf5A7KJHy+3smoy+zGUgmQyScnK4eqjgEipdv0x2I+9zlsl8oPa3Jis5RoQQWxMr"
        "pwIDAQAB"
        "-----END PUBLIC KEY-----"; }

std::string Database::getPrivateServerKey()
{ return "-----BEGIN RSA PRIVATE KEY-----"
        "MIIEowIBAAKCAQEA7hXrrlg3N9Uelmd8X3uTYyrunZwnBqb/RJ0srNxPd+PMe5Da"
        "sw39W6TMDcS7WYgeFIsdlIAfPzWeONKvdCnGINRIJClOHKQOPejAjfISKaCRrdiC"
        "BCQ9hvfqhd7yi9kbWTlkOYtddMceJjwWfEuOIBkaF1F03bOGKNQgXhEbCFTo8ow+"
        "F/lhz7MZXq+pWEpArXwSWFpigVHkAN+5acEYjX/4Pzg9jwrh3NJMffoeFTch3UGF"
        "xY5oQShSGeqFqP4uCb2DvZjNu/aBJxNQHSPztf5A7KJHy+3smoy+zGUgmQyScnK4"
        "eqjgEipdv0x2I+9zlsl8oPa3Jis5RoQQWxMrpwIDAQABAoIBAHVlM6fs8ZVDLejl"
        "sCr4qQ0d7zih9ZBPKdFwWsYFf93S4lIPc/cUL9hPYxpq5iJYftSMYBKINmAZlSHZ"
        "qQ/zRTGM2uGRyGVQ84DNUpzrPs9t0EdTWZCnOftiJS7LZvdUHysYpHXHZVaelBww"
        "RroVG0hyeC4FSUXELqPVLPyVHKo3GICz2FUHR/lj2aKWTSrEJnzEUF+Eg24iVotE"
        "zSGLvLoIGuMer98EX5uhaV5AlfHOfwjZZn//R0eopneJJkil7JnbFNXdznoMIYsd"
        "iVboFSPOPhae7cef++Di2oTnWL3GHefURoAufMvcm1KCYwscCQ3YP2V4+6XnyeEq"
        "vcD3o/ECgYEA+0FjGE8ohhbtHMevM18+aqRfnAG4mVod5QClN2WhwfDlo80l6zyj"
        "HCD0IX9NU8ERDc2OOU6XTWVrwYAWzjZO2hv3VFby8ar0PYD3+pEN1xe3wqfEJCTR"
        "uHs4pGoAAir0/S0jXJZu8o60Y2bYXFWy0iDfJFqtA5QvOBjdaEe/rJkCgYEA8pTe"
        "UujEtryJqQpxIzwYflLb22qxAR33xoUgJe2FngnZS3HEF3rAEPYYMl1uOoZvKQUv"
        "Nk29pvm+6KUMMa+y198rIUS8j7kd/ptE0XO0/MvhH7qOnWjoikZ9OyDDG8Z0lxHI"
        "pHYkWzcAlH/H3SSN9POirCOmWz2agIp79R6Sgj8CgYBc7Gvn267TGLuM/1UOnNUK"
        "v8wUeJZ7MNcJkNmJyW6vuZZUpFS30W9Jwe5ITTqeFTNndXR6QVS37SCTKfpFPdSf"
        "2eP5L0celelKrd4Ir4j82eq+dSmXbH6bygbC1+k05ApDcGQ5o/FYh+qzMKAoVhGS"
        "oVGlslt2jWGBT8DjBlYfUQKBgDJybQ225HnQGZyy1DZsn/ddSeWGeYru7YE2XCon"
        "DBuCltLOtOXhHCIq23tV3L+FB4bzUg8r+Z3I4D/HWxLWJA4qlfCUN9Z3u9of9h7M"
        "vj24NHgBtvjbQUjIQfDS7mBPVB26kAxLmWHyvUckj67YlED1jcXYoBbnZ8MFiaO/"
        "GN7HAoGBAKsMXh7Zw+gntestvbYbye8x9IC7UPjjHObQEzRlYapOtgoX5tavOUu7"
        "xP/7f7OE6j9kqHpB/rsJCSb5GIqyXdPaTjAyZQuJavbiFwUEZ9z9pl0Iii63swPi"
        "/BEVBHlcyCajRYqioVIIPz7yx4SyNoyiPe5BUcvBR0m6ZzuAtMsz"
        "-----END RSA PRIVATE KEY-----"; }