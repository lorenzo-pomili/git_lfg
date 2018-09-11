module.exports = {
  entry: './src/Index.re',
  mode: 'development',
  output: {
    path: __dirname + '/public',
    filename: 'bundle.js'
  },
  devServer: {
      contentBase: __dirname + '/public',
      compress: true,
      port: 8008
  },
  module: {
    rules: [
      {
        test: /\.(re|rei|ml|mli)$/,
        exclude: __dirname+'/node_modules/',
        use: 'bs-loader'
      }
    ]
  },
  resolve: {
    extensions: ['.re', '.ml', '.js']
  }
};
