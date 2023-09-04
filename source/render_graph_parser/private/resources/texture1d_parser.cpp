#include "precompiled_header.h"

#include "texture1d_parser.h"

#include "antlr4_helper.h"

namespace BoolkaEngine::RenderGraphParser {

Texture1D Texture1DParser::Parse(
    ParserContext& parser_context,
    render_graph_parser::ResourceBodyContext* context) {
  return Texture1D{
      .format = ToResourceFormat(Antlr4Helper::GetToken(
          context->resourceFormatDeclaration()->resourceFormatValue())),
      .resolution = Antlr4Helper::AllocateFakeVariable(
          parser_context, context->resolutionDeclaration()->ID()->getText()),
      .optimized_clear_value =
          (context->optimizedClearValueDeclaration()
               ? Antlr4Helper::AllocateFakeVariable(
                     parser_context,
                     context->optimizedClearValueDeclaration()->ID()->getText())
               : nullptr),
      .slice_count =
          (context->sliceCountDeclaration()
               ? Antlr4Helper::AllocateFakeVariable(
                     parser_context,
                     context->sliceCountDeclaration()->ID()->getText())
               : nullptr)};
}

}  // namespace BoolkaEngine::RenderGraphParser