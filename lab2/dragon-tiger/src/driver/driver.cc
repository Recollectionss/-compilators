#include <boost/program_options.hpp>
#include <iostream>

#include "../ast/ast_dumper.hh"
#include "../parser/parser_driver.hh"
#include "../utils/errors.hh"
#include "../ast/evaluator.hh"

int main(int argc, char **argv) {
  std::vector<std::string> input_files;
  namespace po = boost::program_options;
  po::options_description options("Options");
  options.add_options()
  ("help,h", "describe arguments")
  ("dump-ast", "dump the parsed AST")
  ("trace-parser", "enable parser traces")
  ("trace-lexer", "enable lexer traces")
  ("verbose,v", "be verbose")
  ("input-file", po::value(&input_files), "input Tiger file")
  ("eval,e", "Evaluate expression");

  po::positional_options_description positional;
  positional.add("input-file", 1);

  po::variables_map vm;
  po::store(po::command_line_parser(argc, argv)
                .options(options)
                .positional(positional)
                .run(),
            vm);
  po::notify(vm);

  if (vm.count("help")) {
    std::cout << options << "\n";
    return 1;
  }

  if (input_files.size() != 1) {
    utils::error("usage: dtiger [options] input-file");
  }

  const bool dump_ast_flag = vm.count("dump-ast");
  const bool eval_flag = vm.count("eval");


  if (dump_ast_flag && eval_flag) {
    utils::error("Cannot use both --dump-ast and --eval.");
  }

  ParserDriver parser_driver = ParserDriver(vm.count("trace-lexer"), vm.count("trace-parser"));

  if (!parser_driver.parse(input_files[0])) {
    utils::error("parser failed");
  }


  if (eval_flag) {
    ast::Evaluator evaluator;
    parser_driver.result_ast->accept(evaluator);
    std::cout << evaluator.result << std::endl;
    delete parser_driver.result_ast;
    return 0;
  }

  if (vm.count("dump-ast")) {
    ast::ASTDumper dumper(&std::cout, vm.count("verbose") > 0);
    parser_driver.result_ast->accept(dumper);
    dumper.nl();
  }
  delete parser_driver.result_ast;
  return 0;
}
