import pandas as pd
from matplotlib import pyplot as plt
from argparse import ArgumentParser
from pathlib import Path


if __name__ == "__main__":
    ####################
    # Parse arguments

    about = """ Simple plotting script. 
    
    Creates a line plot from two (or more) columns of a provided csv file. 
    If multiple csv files are given, will plot each with a different color
    and label them by their file names!"""

    parser = ArgumentParser(about)
    parser.add_argument(
        "-i", "--input", type=str, nargs="+", required=True, help="csv file to plot"
    )
    parser.add_argument(
        "-x", type=str, default="n", help="the column used for the x axis"
    )
    parser.add_argument(
        "--x_label", type=str, default=None, help="the label for the x-axis"
    )
    parser.add_argument(
        "-y",
        type=str,
        default="error",
        nargs="+",
        help="the column(s) used for the y axis",
    )
    parser.add_argument(
        "--x_scale",
        type=str,
        default="linear",
        help="the scale for the x axis",
    )
    parser.add_argument(
        "--y_scale",
        type=str,
        default="linear",
        help="the scale for the y axis",
    )
    parser.add_argument(
        "--y_label", type=str, default=None, help="the label for the y-axis"
    )
    parser.add_argument(
        "-o",
        "--output",
        type=str,
        default=None,
        help="output file to save to. Will be png format",
    )
    parser.add_argument(
        "--label_by", type=str, default=None, help="color/label curves by this column"
    )
    parser.add_argument(
        "--exclude_column",
        type=str,
        nargs="+",
        default=[],
        help="filter based on this column",
    )
    parser.add_argument(
        "--exclude_value",
        type=str,
        nargs="+",
        default=[],
        help="filter based on this value",
    )

    args = parser.parse_args()
    if not isinstance(args.y, list):
        args.y = [args.y]

    ####################
    # Read and plot results

    fig, ax = plt.subplots(
        nrows=1, ncols=1
    )  # create figure & 1 axis # will want to plot on the same axis!

    for input in args.input:
        input = Path(input)
        if not input.exists():
            raise FileNotFoundError(f"The requested input {input} does not exist!")
        df = pd.read_csv(input)
        if not args.x in df.columns:
            raise ValueError(f'Expected a column called "{args.x}" in your input csv!')

        for y in args.y:
            if not y in df.columns:
                raise ValueError(f'Expected a column called "{y}" in your input csv!')

        if not args.label_by in df.columns:
            raise ValueError(
                f"Expected a column called {args.label_by} in your input csv!"
            )

        # filter out rows that don't match the exclude criteria
        for column, value in zip(args.exclude_column, args.exclude_value):
            df = df[df[column] != value]

        if args.label_by is not None:
            for group, data in df.groupby(args.label_by):
                for y in args.y:
                    data.plot.line(
                        args.x,
                        y,
                        ax=ax,
                        title=", ".join(args.y) + f" vs {args.x}",
                        xlabel=args.x_label,
                        ylabel=args.y_label,
                        label=str(input.stem) + f".{group}.{y}",
                    )

        else:
            for y in args.y:
                df.plot.line(
                    args.x,
                    y,
                    ax=ax,
                    title=", ".join(args.y) + f" vs {args.x}",
                    xlabel=args.x_label,
                    ylabel=args.y_label,
                    label=str(input.stem) + f".{y}",
                )
    ax.legend()

    ##############################
    # Either show or save results

    plt.xscale(args.x_scale)
    plt.yscale(args.y_scale)

    if args.output is None:
        plt.show()
    else:
        fig.savefig(args.output)
