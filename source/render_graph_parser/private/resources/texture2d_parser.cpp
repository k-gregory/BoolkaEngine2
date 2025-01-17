#include "precompiled_header.h"

#include "texture2d_parser.h"

#include "antlr4_helper.h"

namespace BoolkaEngine::RenderGraphParser {

Texture2D Texture2DParser::Parse(
    ParserContext& parser_context,
    render_graph_parser::ResourceBodyContext* context) {
  return Texture2D{
      .format = ToResourceFormat(Antlr4Helper::GetToken(
          context->resourceFormatDeclaration()->resourceFormatValue())),
      .resolution_name = Antlr4Helper::GetID(
          parser_context, context->resolutionDeclaration(), false),
      .optimized_clear_value_name = Antlr4Helper::GetID(
          parser_context, context->optimizedClearValueDeclaration()),
      .slice_count_name = Antlr4Helper::GetID(
          parser_context, context->sliceCountDeclaration())};
}

void Texture2DParser::Linkup(const RenderGraph& graph, Texture2D& texture) {
  texture.resolution =
      Antlr4Helper::GetVariable(graph, texture.resolution_name, false);
  texture.optimized_clear_value =
      Antlr4Helper::GetVariable(graph, texture.optimized_clear_value_name);
  texture.slice_count =
      Antlr4Helper::GetVariable(graph, texture.slice_count_name);
}

}  // namespace BoolkaEngine::RenderGraphParser
