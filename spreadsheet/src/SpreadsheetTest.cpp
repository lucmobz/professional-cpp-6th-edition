import std;
import spreadsheet;

static auto createSpreadsheetRVO(const SpreadsheetApplication& app)
    -> Spreadsheet {
  return Spreadsheet{app, 2, 2};
}

static auto createSpreadsheetNRVO(const SpreadsheetApplication& app)
    -> Spreadsheet {
  Spreadsheet spreadsheet{app, 2, 2};
  return spreadsheet;
}

static auto createSpreadsheetBraces(const SpreadsheetApplication& app)
    -> Spreadsheet {
  return {app, 2, 2};
}

auto main() -> int {
  SpreadsheetApplication app1;
  SpreadsheetApplication app2;

  // These three have max copy-elision
  auto s1{createSpreadsheetRVO(app1)};
  auto s2{createSpreadsheetNRVO(app2)};
  auto s3{createSpreadsheetBraces(app1)};

  std::vector<Spreadsheet> spreadsheets;
  spreadsheets.reserve(4);

  // These do an unnecessary move
  spreadsheets.emplace_back(Spreadsheet{app1, 2, 2});
  // This will not create a copy of the application as {} is not a type, just a
  // way to initialize objects. A spreadsheet copy is made and then it is moved
  spreadsheets.push_back({app2, 2, 2});
  spreadsheets.push_back(Spreadsheet{app2, 2, 2});

  // Does not compile, it is a template function
  // spreadsheets.emplace_back({app1, 2, 2});

  // Best way is to just constructs in-place
  spreadsheets.emplace_back(app1, 2, 2);

  // Using the move-swap idiom
  spreadsheets[0] = createSpreadsheetRVO(app1);
  spreadsheets[0] = createSpreadsheetNRVO(app1);
  spreadsheets[0] = createSpreadsheetBraces(app1);
}