pub fn welcome() {
    let welcome_msg
        = String::from("Welcome to use the quality key number Cpk and Cp calculator.");
    let welcome_size = welcome_msg.len();
    let box_symbol = "#";
    
    println!("{}", box_symbol.repeat(welcome_size + 6));
    println!("{}{}{}", box_symbol, " ".repeat(welcome_size + 4), box_symbol);
    println!("{}  {}  {}", box_symbol, welcome_msg, box_symbol);
    println!("{}{}{}", box_symbol, " ".repeat(welcome_size + 4), box_symbol);
    println!("{}\n", box_symbol.repeat(welcome_size + 6));
}

pub fn data_input() -> Result<(f64, f64, f64, Vec<f64>), ()> {
    use std::io::Write;
    let design_measure: f64;
    loop {
        print!("Enter the design value for the measure: ");
        std::io::stdout().flush().unwrap();
        design_measure = match design_info() {
            Ok(f) => f,
            Err(_) => {
                continue;
            }
        };
        break;
    }

    let upper_tolerance: f64;
    loop {
        print!("Enter the upper tolerance limit for the measure: ");
        std::io::stdout().flush().unwrap();
        upper_tolerance = match design_info() {
            Ok(f) => f,
            Err(_) => {
                continue;
            }
        };
        break;
    }
    
    let lower_tolerance: f64;
    loop {
        print!("Enter the lower tolerance limit for the measure: ");
        std::io::stdout().flush().unwrap();
        lower_tolerance = match design_info() {
            Ok(f) => f,
            Err(_) => {
                continue;
            }
        };
        break;
    }

    println!();

    let mut data: Vec<f64> = vec![];
    let mut i = 1;

    loop {
        let mut input: String = String::new();

        print!("Enter measurement for part number {} (0 = stop): ", i);
        std::io::stdout().flush().unwrap();

        match std::io::stdin().read_line(&mut input) {
            Ok(_) => (),
            Err(_) => {
                println!("Couldn't read input");
                continue;
            }
        };

        if input.trim() == "0" {
            break;
        }

        let measure = match input.trim().parse::<f64>() {
            Ok(f) => f,
            Err(_) => {
                println!("Not a float number");
                continue;
            }
        };

        data.push(measure);
        i += 1;
    }
    return Ok((design_measure, upper_tolerance, lower_tolerance, data));
}

pub fn design_info() -> Result<f64, ()> {
    let mut input = String::new();
    match std::io::stdin().read_line(&mut input) {
        Ok(_) => (),
        Err(_) => {
            println!("Couldn't read input");
        }
    };

    let design_info = match input.trim().parse::<f64>() {
        Ok(f) => f,
        Err(_) => {
            println!("Not a float number");
            return Err(());
        }
    };
    Ok(design_info)
}

pub fn standard_deviation(data: &Vec<f64>) -> (f64, f64) {
    let mut mean: f64 = data.iter().map(|values| *values).sum();
    mean = mean / data.len() as f64;

    // squared mean by doing (x - X)^2 over the values of the vector
    let squared_mean: f64 = data.iter().map(|values| (*values - mean).powf(2.0)).sum();

    // the actual standard deviation (-1 is a correction in big measurements)
    let stddev: f64 = (squared_mean / (data.len() as f64 - 1.0)).sqrt();
    return (stddev, mean);
}

pub fn quality_numbers(s: &f64, mean: &f64, tol_range: &f64,
                        up_limit: &f64, low_limit: &f64) -> (f64, f64, f64) {
    let cpk_up = (up_limit - mean) / (3.0 * s);
    let cpk_low = (mean - low_limit) / (3.0 * s);
    let cp = tol_range / (6.0 * s);

    return (cpk_up, cpk_low, cp);
}

pub fn print_results(cpk_up: &f64, cpk_low: &f64, cp: &f64) {
    println!();
    println!("{}\n", "-".repeat(80));
    println!("Upper Cpk is {:.3}\nLower Cpk is {:.3}\nThe Cp is {:.3}\n",
        &cpk_up, &cpk_low, &cp);
    println!("{}\n", "-".repeat(80));
}

fn main() {
    // test values, uncomment to use them
    // let design_measure = 451.5;
    // let up_tolerance = 0.3;
    // let low_tolerance = -0.2;
    // let tol_range = up_tolerance - low_tolerance;
    // let up_limit = up_tolerance + design_measure;
    // let low_limit = low_tolerance + design_measure;
    // let data = vec![451.1, 451.7, 451.5, 452.0, 451.7, 452.3, 452.4, 450.9];
    
    welcome();

    // get all the desired measure, tolerance and measurement data in a function
    let result = data_input().unwrap();
    let (design_measure, up_tolerance, low_tolerance, data)
        = (result.0, result.1, result.2, result.3);

    let tol_range = up_tolerance - low_tolerance;
    let up_limit = up_tolerance + design_measure;
    let low_limit = low_tolerance + design_measure;

    // usually you only calculate standard deviation for measurements with
    // more than ten measurements
    let result = standard_deviation(&data);
    let (stddev, mean) = (result.0, result.1);

    // println!("The standard deviation is {:.3}\n", &stddev);

    // calculate cpk and cp in a function
    let result = quality_numbers(&stddev, &mean, &tol_range,
                                                    &up_limit, &low_limit);
    let (cpk_up, cpk_low, cp) = (result.0, result.1, result.2);

    print_results(&cpk_up, &cpk_low, &cp);

    loop {
        println!("Press any key to exit...");
        std::io::stdin().read_line(&mut String::new()).ok();
        break;
    }
}
