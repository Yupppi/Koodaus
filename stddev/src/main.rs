pub fn standard_deviation(data: &Vec<f64>) -> (f64, f64) {
    let mut mean: f64 = data.iter().map(|values| *values).sum();
    mean = mean / data.len() as f64;

    // squared mean by doing (x - X)^2 over the values of the vector
    let squared_mean: f64 = data.iter().map(|values| (*values - mean).powf(2.0)).sum();

    // the actual standard deviation (-1 is a correction in big measurements)
    let stddev: f64 = (squared_mean / (data.len() as f64 - 1.0)).sqrt();
    return (stddev, mean);
}

pub fn quality_numbers( s: &f64, mean: &f64, tolerance_range: &f64,
                        up_limit: &f64, low_limit: &f64 ) -> (f64, f64, f64) {
    let cpk_up = (up_limit - mean) / (3.0 * s);
    let cpk_low = (mean - low_limit) / (3.0 * s);
    let cp = tolerance_range / (6.0 * s);

    return (cpk_up, cpk_low, cp);
}

fn main() {
    // assigning test values
    let design_measure = 451.5;
    let up_tolerance = 0.3;
    let low_tolerance = -0.2;
    let tolerance_range = up_tolerance - low_tolerance;
    let up_limit = up_tolerance + design_measure;
    let low_limit = low_tolerance + design_measure;
    let data = vec![451.1, 451.7, 451.5, 452.0, 451.7, 452.3, 452.4, 450.9];

    // calculate the mean, squared mean and standard deviation in the function
    // usually you only calculate standard deviation for measurements with
    // more than ten measurements
    let result = standard_deviation(&data);
    let (stddev, mean) = (result.0, result.1);

    println!("The standard deviation is {:.3}", stddev);

    // calculate cpk and cp in a function
    let result = quality_numbers(&stddev, &mean, &tolerance_range,
                                                    &up_limit, &low_limit);
    let (cpk_up, cpk_low, cp) = (result.0, result.1, result.2);

    println!(
        "Upper Cpk is {:.3}\nLower Cpk is {:.3}\nThe Cp is {:.3}",
        cpk_up, cpk_low, cp
    );
}
